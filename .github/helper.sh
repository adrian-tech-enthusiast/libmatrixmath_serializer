#!/bin/bash
#
# @file helper.sh
# @brief Helper functions for building and managing the project.
#
# This script contains various helper functions that are used for building the project,
# managing build directories, and creating shared and static libraries. These functions
# are meant to be sourced by other scripts, such as build.sh, to facilitate common tasks.
#
# @usage
# Source this script in other bash scripts to use the provided functions:
#   source /path/to/helper.sh;
#
# Functions provided:
# - get_files_to_compile: Retrieves a list of header and source files to compile.
# - clean_directory: Cleans up a specified directory.
# - build_app: Builds the main application executable.
# - create_libraries: Creates shared and static libraries from source files.
# - install_library_from_local: Installs shared libraries and header files locally from local source code.
# - install_library_from_remote: Installs shared libraries and header files from a remote GitHub repository.
# - remove_precompiled_headers: Removes precompiled header files from a specified directory.
# - clean_project_precompiled_headers: Cleans precompiled header files from the project directories.
# - ensure_sudo: Ensures the script or function is run with sudo privileges.
# - build_project: Orchestrates the entire build process for the project.

# Function to get the list of code files to compile.
#
# Arguments:
#   $1 - Space-separated list of directories to search for code files.
#
# Outputs:
#   Space-separated list of .h and .c files found in the specified directories.
#
# Usage:
#   files_to_compile=$(get_files_to_compile "$SEARCH_PATHS");
get_files_to_compile() {
  local code_search_paths=$1;
  local header_files=$(find $code_search_paths -maxdepth 3 -type f -name "*.h" ! -path '*/\.*' | sort);
  local source_files=$(find $code_search_paths -maxdepth 3 -type f -name "*.c" ! -path '*/\.*' | sort);
  echo "$header_files $source_files";
}

# Function to clean up a directory.
#
# Arguments:
#   $1 - Directory to clean up.
#
# Usage:
#   clean_directory "$DIR_PATH";
clean_directory() {
  local dir=$1;
  rm -rf "$dir" && mkdir -p "$dir";
}

# Function to build the project.
#
# Arguments:
#   $1 - Space-separated list of files to compile.
#   $2 - Path to the build directory.
#   $3 - Name of the application to be created.
#   $4 - Space-separated list of dependencies for the build.
#   $5 - Path to the directory where the binary should be moved.
#
# Usage:
#   build_app "$FILES_TO_COMPILE" "$BUILD_PATH" "$APP_NAME" "$DEPENDENCIES" "$BIN_PATH";
build_app() {
  # Get arguments.
  local files_to_compile=$1;
  local build_path=$2;
  local app_name=$3;
  local dependencies=$4;
  local bin_path=$5;
  local current_path=$(pwd);

  # clean up build and bin folder.
  clean_directory "$build_path";
  clean_directory "$bin_path";

  # Go to the build path.
  cd "$build_path" || exit;

  # Compile the given files.
  gcc -O3 -march=native -g -fpic -save-temps -Wall -Werror -pedantic-errors -o "$app_name" $files_to_compile $dependencies;
  if [ $? -ne 0 ]; then
    echo "Compile Failed!";
    exit 1;
  fi

  # Add executable permistions to the build app;
  local app_file="$build_path/$app_name";
  if [ -f "$app_file" ]; then
    chmod +x "$app_file";
  fi

  # Move executables to the bin directory.
  mv $app_name $bin_path || exit;

  # Go back to where we were before.
  cd "$current_path" || exit;
}

# Function to create shared and static libraries.
#
# Arguments:
#   $1 - Space-separated list of files to compile.
#   $2 - Path to the build directory.
#   $3 - Base name of the library to be created.
#   $4 - Space-separated list of dependencies for the build.
#   $5 - Path to the directory where the libraries should be moved.
#
# Usage:
#   create_libraries "$FILES_TO_COMPILE" "$BUILD_PATH" "$LIBRARY_NAME" "$DEPENDENCIES" "$BIN_PATH";
create_libraries() {
  # Get arguments.
  local files_to_compile=$1;
  local build_path=$2;
  local library_name=$3;
  local dependencies=$4;
  local bin_path=$5;
  local current_path=$(pwd);

  # Clean up build folder and previous compiled libraries.
  clean_directory "$build_path";
  rm -rf "$bin_path/$library_name.so";
  rm -rf "$bin_path/$library_name.a";

  # Go to the build path.
  cd "$build_path" || exit;

  # Build the objects for the library.
  gcc -O3 -shared -march=native -g -fpic -save-temps -Wall -Werror -pedantic-errors $files_to_compile $dependencies;
  if [ $? -ne 0 ]; then
    echo "Compile Failed!";
    exit 1;
  fi

  # Get the object files to include in the library;
  local obj_files=$(find $build_path -type f -name "*.o" ! -path '*/\.*' | sort);

  # Create single shared library file from the object module(s).
  gcc -shared -Wno-undef -Wl,-soname,$library_name.so -o $library_name.so $obj_files $dependencies -L$build_path;
  if [ $? -ne 0 ]; then
    echo "Compile Failed!";
    exit 1;
  fi

  # Create the static library (archive) from the object files using the ar tool.
  ar rcs "$build_path/$library_name.a" $obj_files;

  # Move executables to the bin directory.
  mv "$build_path/$library_name.so" "$bin_path" || exit;
  mv "$build_path/$library_name.a" "$bin_path" || exit;

  # Go back to where we were before.
  cd "$current_path" || exit;
}

# Function to ensure the script is run with sudo.
#
# This function checks if the script is being run with root or sudo privileges.
# If not, it prints an error message and exits the script.
#
# Call this function at the beginning of scripts or functions that require root or sudo privileges.
#
# Usage:
#   ensure_sudo;
ensure_sudo() {
  if [[ $EUID -ne 0 ]]; then
    echo "Error: This script requires root or sudo privileges to install libraries.";
    exit 1;
  fi
}

# Installs shared libraries and header files locally from local source code.
#
# Arguments:
#   $1: Path to the directory containing shared library files (*.so).
#   $2: Path to the directory containing header files (*.h).
#
# Usage:
#   install_library_from_local "/path/to/libraries" "/path/to/headers";
install_library_from_local() {
  # Ensure the script has appropriate privileges.
  ensure_sudo;

  # Get arguments.
  local bin_path="$1"
  local include_path="$2"

  # Check if paths are provided.
  if [[ -z "$bin_path" || -z "$include_path" ]]; then
    echo "Error: Both library and header paths must be provided.";
    exit 1;
  fi

  # Install shared library files to "/usr/local/lib" folder.
  local library_files=$(find "$bin_path" -maxdepth 3 -type f -name "*.so" ! -path '*/\.*' | sort);
  for file in $library_files; do
    # Extract the name of the .so file and print a friendly message.
    library_name=$(basename "$file");
    echo "Installing $library_name library into '/usr/local/lib/'..."
    # Install the library.
    cp "$file" /usr/local/lib/;
    # Check if the file was successfully copied.
    if [[ ! -f "/usr/local/lib/$library_name" ]]; then
      echo "Error: Failed to install $library_name library."
      exit 1
    fi
  done

  # Install header files to /usr/local/include.
  local include_files=$(find "$include_path" -maxdepth 3 -type f -name "*.h" ! -path '*/\.*' | sort);
  for file in $include_files; do
    # Extract the name of the .h file and print a friendly message.
    header_name=$(basename "$file");
    echo "Installing $header_name header into '/usr/local/include/'..."
    cp "$file" /usr/local/include/;
    # Check if the file was successfully copied.
    if [[ ! -f "/usr/local/include/$header_name" ]]; then
      echo "Error: Failed to install $header_name header."
      exit 1
    fi
  done
}

# Function to download and install a shared library and its header file from GitHub.
#
# Arguments:
#   $1: Repository owner (e.g., "adrian-tech-enthusiast").
#   $2: Repository name (e.g., "libstr").
#   $3: Library version (e.g., "v1.0.1").
#   $4: Library name (e.g., "libstr.so").
#   $5: Header file name (e.g., "strutils.h").
#
# Usage:
#   install_library_from_remote "adrian-tech-enthusiast" "libstr" "v1.0.1" "libstr.so" "strutils.h";
install_library_from_remote() {
  # Ensure the script has appropriate privileges.
  ensure_sudo;

  # Get arguments.
  local repo_owner=$1
  local repo_name=$2
  local library_version=$3
  local library_name=$4
  local header_name=$5

  # Check if all required arguments are provided.
  if [[ -z "$repo_owner" || -z "$repo_name" || -z "$library_version" || -z "$library_name" || -z "$header_name" ]]; then
    echo "Error: Missing arguments. All arguments must be provided."
    echo "Usage: install_library_from_remote <repo_owner> <repo_name> <library_version> <library_name> <header_name>"
    exit 1
  fi

  # Build paths URLs an Paths variables.
  local lib_url="https://github.com/$repo_owner/$repo_name/releases/download/$library_version/$library_name";
  local header_url="https://raw.githubusercontent.com/$repo_owner/$repo_name/$library_version/include/$header_name";
  local lib_dest_path="/usr/local/lib";
  local header_dest_path="/usr/local/include";
  local temp_lib_path="/tmp/$library_name";
  local temp_header_path="/tmp/$header_name";

  # Download the shared library.
  echo "Downloading $library_name";
  if curl -L "$lib_url" -o "$temp_lib_path"; then
    mv "$temp_lib_path" "$lib_dest_path";
    ldconfig;
    ldconfig -p | grep "${library_name%.so}";
  else
    echo "Error: Failed to download $library_name";
    rm -f "$temp_lib_path";
    exit 1;
  fi

  # Download the header file.
  echo "Downloading $header_name";
  if curl -L "$header_url" -o "$temp_header_path"; then
    mv "$temp_header_path" "$header_dest_path";
  else
    echo "Error: Failed to download $header_name";
    rm -f "$temp_header_path";
    exit 1;
  fi

  # Cleanup temporary files.
  rm -f "$temp_lib_path" "$temp_header_path";
}

# Function to remove precompiled header files from a specified directory.
#
# Arguments:
#   $1: Path to the directory to clean.
#
# Usage:
#   remove_precompiled_headers "/path/to/directory";
remove_precompiled_headers() {
   # Get arguments.
   local dir_path="$1";

   # Ger the list of precompiled header files to remove.
   local precompiled_files=$(find "$dir_path" -maxdepth 3 -type f -name "*.h.gch" ! -path '*/\.*' | sort);

   # Remove precompiled header files.
   for file in $precompiled_files; do
     local precompiled_file_name=$(basename "$file");
     echo "Removing precompiled header file $precompiled_file_name from $dir_path...";
     rm -rf "$file";
   done
}

# Function to clean precompiled header files from the project directories.
#
# Arguments:
#   $1: Path to the root of the project.
#
# Usage:
#   clean_project_precompiled_headers "/path/to/project";
clean_project_precompiled_headers() {
  # Get arguments.
  local project_path=$1;

  # Validate the project path argument.
  if [[ -z "$project_path" ]]; then
    echo "Error: Project path must be provided.";
    exit 1;
  fi

  # Remove precompiled header files from specified directories.
  remove_precompiled_headers "$project_path/src";
  remove_precompiled_headers "$project_path/include";
  remove_precompiled_headers "$project_path/tests";
}

# Function to build the project.
#
# Arguments:
#   $1: Base name for the project.
#   $2: Root path of the project.
#   $3: Dependencies for tests.
#   $4: Dependencies for libraries.
#   $5: The project namespace.
#
# Usage:
#   build_project "project_base_name" "/path/to/project" "test_dependencies" "library_dependencies" "namespace";
build_project() {
  # Get arguments.
  local base_name="$1"; # Base name for the project.
  local project_path="$2"; # Root path of the project.
  local test_dependencies="$3"; # Dependencies for tests.
  local library_dependencies="$4"; # Dependencies for libraries.
  local project_namespace="$5"; # The project namespace.

  # Search paths for library and test code.
  local library_code_search_paths="$project_path/include $project_path/src/$project_namespace";
  local test_code_search_paths="$library_code_search_paths $project_path/tests/$project_namespace";

  # Build paths.
  local base_build_path="$project_path/build/$project_namespace";
  local library_build_path="$base_build_path/library";
  local test_build_path="$base_build_path/test";

  # Output paths.
  local bin_path="$project_path/bin";
  local app_name="$base_name.app";

  # Clean up build directory before start the build.
  clean_directory "$base_build_path";

  # Build the main app.
  local app_files_to_compile;
  app_files_to_compile=$(get_files_to_compile "$test_code_search_paths");
  build_app "$app_files_to_compile" $test_build_path $app_name "$test_dependencies" $bin_path;

  # Create shared and static libraries.
  local library_files_to_compile;
  library_files_to_compile=$(get_files_to_compile "$library_code_search_paths");
  create_libraries "$library_files_to_compile" $library_build_path $base_name "$library_dependencies" $bin_path;

  # Clean precompiled header files from the project directories.
  clean_project_precompiled_headers "$project_path" > /dev/null;

  # Test the APP execution.
  "$bin_path/$app_name";
}

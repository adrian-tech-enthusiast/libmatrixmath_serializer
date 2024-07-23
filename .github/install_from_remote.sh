#!/bin/bash

# @file install_from_remote.sh
# @brief Script download and install a shared library and its header file from GitHub.
#
# This script automates the installation of shared libraries and header files
# into system directories for local development or deployment. It utilizes helper
# functions from "helper.sh" to perform these tasks.


# Determine the directory of the script.
SCRIPT_DIR=$(dirname "$(readlink -f "$0")");
# Load helper functions.
source "$SCRIPT_DIR/helper.sh";

# Ensure that library dependencies are installed on the local system.
install_dependencies_from_remote() {
   # Install 'libmatrixmath' library dependency locally from remote(Github repo).
   install_library_from_remote "adrian-tech-enthusiast" "libmatrixmath" "v1.1.5" "libmatrixmath.so" "matrixmath.h";

   # Install 'lstr' library dependency locally from remote(Github repo).
   install_library_from_remote "adrian-tech-enthusiast" "lstr" "v1.1.0" "libstr.so" "strutils.h";

   # Install 'libjson' library dependency locally from remote(Github repo).
   install_library_from_remote "adrian-tech-enthusiast" "libjson" "v1.1.0" "libjson.so" "json.h";
}

# Call the function.
install_dependencies_from_remote;
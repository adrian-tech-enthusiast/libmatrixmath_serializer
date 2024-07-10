#!/bin/bash

# @file install_from_local.sh
# @brief Script for installing shared libraries and header files locally from local source code.
#
# This script automates the installation of shared libraries and header files
# into system directories for local development or deployment. It utilizes helper
# functions from "helper.sh" to perform these tasks.


# Determine the directory of the script.
SCRIPT_DIR=$(dirname "$(readlink -f "$0")");
# Load helper functions.
source "$SCRIPT_DIR/helper.sh";

# Global Settings.
PROJECT_PATH=$(pwd);
BIN_PATH="$PROJECT_PATH/bin";
INCLUDE_PATH="$PROJECT_PATH/include";

# Install library locally from local source code.
install_library_from_local "$BIN_PATH" "$INCLUDE_PATH";

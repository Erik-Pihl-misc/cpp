#!/bin/bash

################################################################################
# Builds the project and runs specified executable.
################################################################################
cd build               # Redirects to the build directory.
make                   # Builds the project with CMake.
cd ..                  # Redirects to the base directory.
if [[ -n "$1" ]]; then # Runs executable in the output directory if specified.
    ./output/$1            
fi

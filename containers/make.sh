#!/bin/bash

################################################################################
# Builds the project and runs specified executable.
################################################################################
cd build    # Redirects to the build directory.
make        # Builds the project with CMake.
cd ..       # Redirects to the base directory.
./output/$1 # Runs specified executable in the output directory.
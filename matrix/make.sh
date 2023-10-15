#!/bin/bash

################################################################################
# @brief Builds the project and runs the "run_matrix" executable.
################################################################################
cd build     # Redirects to the build directory.
make         # Builds the project with CMake.
cd ..        # Redirects to the base directory.
./run_matrix # Runs the program.
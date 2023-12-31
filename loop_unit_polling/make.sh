#!/bin/bash

################################################################################
# @brief Functions for building and running executables with CMake.
################################################################################
BUILD_DIR=build
OUTPUT_DIR=out
EXECUTABLE=$OUTPUT_DIR/run_loop_unit_polling

################################################################################
# @brief Creates new build.
################################################################################
init() {
    cd $BUILD_DIR
    cmake CMakeLists.txt
    make
    cd ..
}

################################################################################
# @brief Builds the project and creates a new executable.
################################################################################
build() {
    cd $BUILD_DIR
    make 
    cd ..
}

################################################################################
# @brief Runs the executable. 
################################################################################
run() {
    ./$EXECUTABLE
}

################################################################################
# @brief Builds and runs the executable. 
################################################################################
build_and_run() {
    build
    run
}

################################################################################
# @brief Creates a new build.
################################################################################
clean() {
    rm $BUILD_DIR/CMakeCache.txt
    init 
}

"$@"
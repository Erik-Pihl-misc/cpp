cmake_minimum_required(VERSION 3.20)
project(containers_cpp)
include_directories(../inc)

add_executable(run_array_demo ../src/array_demo.cpp)
target_compile_options(run_array_demo PRIVATE -Wall -Werror)
set_target_properties(run_array_demo PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../output)
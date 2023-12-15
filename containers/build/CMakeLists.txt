cmake_minimum_required(VERSION 3.20)
project(containers_cpp)
include_directories(../inc)

add_executable(run_array_demo ../src/array_demo.cpp)
target_compile_options(run_array_demo PRIVATE -Wall -Werror)
set_target_properties(run_array_demo PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../output)

add_executable(run_vector_demo ../src/vector_demo.cpp)
target_compile_options(run_vector_demo PRIVATE -Wall -Werror)
set_target_properties(run_vector_demo PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../output)

add_executable(run_list_demo ../src/list_demo.cpp)
target_compile_options(run_list_demo PRIVATE -Wall -Werror)
set_target_properties(run_list_demo PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../output)
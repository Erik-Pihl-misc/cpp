cmake_minimum_required(VERSION 3.20)
project(containers_cpp)
include_directories(../inc)

add_executable(array_demo ../src/array_demo.cpp)
target_compile_options(array_demo PRIVATE -Wall -Werror)
set_target_properties(array_demo PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../output)

add_executable(vector_demo ../src/vector_demo.cpp)
target_compile_options(vector_demo PRIVATE -Wall -Werror)
set_target_properties(vector_demo PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../output)

add_executable(list_demo ../src/list_demo.cpp)
target_compile_options(list_demo PRIVATE -Wall -Werror)
set_target_properties(list_demo PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../output)
cmake_minimum_required(VERSION 3.20)
project(neural_network)

set(INCLUDE_DIRS ../inc)
set(SOURCE_DIR ../src)
set(OUTPUT_DIR ../out)
set(SOURCE_FILES ${SOURCE_DIR}/main.cpp 
                 ${SOURCE_DIR}/dense_layer.cpp 
                 ${SOURCE_DIR}/neural_network.cpp)
set(COMPILE_FLAGS -Wall -Werror)
set(EXECUTABLE "run_${PROJECT_NAME}")
set(PROPERTIES CXX_STANDARD 17)

include_directories(${INCLUDE_DIRS})
add_executable(${EXECUTABLE} ${SOURCE_FILES})
target_compile_options(${EXECUTABLE} PRIVATE ${COMPILE_FLAGS})
set_target_properties(${EXECUTABLE} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set_property(TARGET ${EXECUTABLE} PROPERTY ${PROPERTIES})
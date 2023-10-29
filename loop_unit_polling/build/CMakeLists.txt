cmake_minimum_required(VERSION 3.20)
project(loop_unit_polling)

set(INCLUDE_DIRS ../inc)
set(SOURCE_DIR ../src)
set(OUTPUT_DIR ../out)
set(COMPILE_FLAGS -Wall -Werror)
set(PROPERTIES CXX_STANDARD 17)
set(EXECUTABLE "run_${PROJECT_NAME}")
set(SOURCE_FILES ${SOURCE_DIR}/main.cpp 
                 ${SOURCE_DIR}/sensor.cpp
                 ${SOURCE_DIR}/timer.cpp)

include_directories(${INCLUDE_DIRS})
add_executable(${EXECUTABLE} ${SOURCE_FILES})
target_compile_options(${EXECUTABLE} PRIVATE ${COMPILE_FLAGS})
target_link_libraries(${EXECUTABLE} ${LIBRARIES})
set_target_properties(${EXECUTABLE} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set_property(TARGET ${EXECUTABLE} PROPERTY ${PROPERTIES})

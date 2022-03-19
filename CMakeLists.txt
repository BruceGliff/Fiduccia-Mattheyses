cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME Initial)
project(${PROJECT_NAME})

file(GLOB_RECURSE SRC_FILES src/lib/*.cc)
add_executable(${PROJECT_NAME} src/main.cc ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/include)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -O0 -g )

set(OUT_DIR ${CMAKE_BINARY_DIR}/bin/)
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUT_DIR})

add_custom_command(	TARGET ${PROJECT_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/benchmark/ ${OUT_DIR}/benchmark/)

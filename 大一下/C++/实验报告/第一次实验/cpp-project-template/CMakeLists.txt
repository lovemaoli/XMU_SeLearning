cmake_minimum_required(VERSION 3.10)

project(cpp-project-template)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)
string(TIMESTAMP BUILD_DATE "%Y%m%d")

configure_file(${PROJECT_SOURCE_DIR}/config.h.in config.h @ONLY)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(cpp-template src/main.cpp)
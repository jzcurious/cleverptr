cmake_minimum_required(VERSION 3.24...3.30)
project(cleverptr-lib LANGUAGES CXX)

add_library(cleverptr INTERFACE)

target_include_directories(cleverptr INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

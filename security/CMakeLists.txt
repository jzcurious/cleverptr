cmake_minimum_required(VERSION 3.24...3.30)
project(cleverptr-security LANGUAGES CXX)

add_executable(cleverptr-security
    ${CMAKE_CURRENT_SOURCE_DIR}/src/security.cpp
)

target_link_libraries(cleverptr-security PRIVATE
    cleverptr
)

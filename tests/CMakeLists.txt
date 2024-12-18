cmake_minimum_required(VERSION 3.24...3.30)
project(cleverptr-tests LANGUAGES CXX)

include(GoogleTest)
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)

FetchContent_MakeAvailable(googletest)

add_executable(cleverptr-tests
    ${CMAKE_CURRENT_SOURCE_DIR}/src/tests.cpp
)

target_link_libraries(cleverptr-tests PRIVATE
    cleverptr
    GTest::gtest_main
)

enable_testing()
gtest_discover_tests(cleverptr-tests)

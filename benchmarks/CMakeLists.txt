cmake_minimum_required(VERSION 3.24...3.30)
project(cleverptr-benchmarks LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
  benchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG v1.9.0
)

FetchContent_MakeAvailable(benchmark)

add_executable(cleverptr-benchmarks
    ${CMAKE_CURRENT_SOURCE_DIR}/src/benchmarks.cpp
)

target_include_directories(cleverptr-benchmarks PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../cleverptr/include
)

target_link_libraries(cleverptr-benchmarks PRIVATE
    benchmark::benchmark
)

#include "benchmark/benchmark.h"
#include "shptr.hpp"
#include <memory>

static void swap_std_shared_ptr(benchmark::State& state) {
  auto ptr1 = std::make_shared<std::vector<float>>(100);
  auto ptr2 = std::make_shared<std::vector<float>>(100);
  auto ptr3 = std::make_shared<std::vector<float>>(100);

  for (auto _ : state) {
    benchmark::DoNotOptimize(ptr3 = ptr2);
    benchmark::DoNotOptimize(ptr2 = ptr1);
    benchmark::DoNotOptimize(ptr1 = ptr3);
  }
}

static void swap_cleverptr_shptr(benchmark::State& state) {
  auto ptr1 = cleverptr::make_shared<std::vector<float>>(100);
  auto ptr2 = cleverptr::make_shared<std::vector<float>>(100);
  auto ptr3 = cleverptr::make_shared<std::vector<float>>(100);

  for (auto _ : state) {
    benchmark::DoNotOptimize(ptr3 = ptr2);
    benchmark::DoNotOptimize(ptr2 = ptr1);
    benchmark::DoNotOptimize(ptr1 = ptr3);
  }
}

BENCHMARK(swap_cleverptr_shptr);
BENCHMARK(swap_std_shared_ptr);
BENCHMARK_MAIN();

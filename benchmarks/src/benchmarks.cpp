#include "benchmark/benchmark.h"
#include "shptr.hpp"
#include "uniptr.hpp"
#include <memory>

static void shared_std_swap(benchmark::State& state) {
  auto ptr1 = std::make_shared<std::vector<float>>(100);
  auto ptr2 = std::make_shared<std::vector<float>>(100);
  auto ptr3 = std::make_shared<std::vector<float>>(100);

  for (auto _ : state) {
    benchmark::DoNotOptimize(ptr3 = ptr2);
    benchmark::DoNotOptimize(ptr2 = ptr1);
    benchmark::DoNotOptimize(ptr1 = ptr3);
  }
}

static void shared_cleverptr_swap(benchmark::State& state) {
  auto ptr1 = cleverptr::make_shared<std::vector<float>>(100);
  auto ptr2 = cleverptr::make_shared<std::vector<float>>(100);
  auto ptr3 = cleverptr::make_shared<std::vector<float>>(100);

  for (auto _ : state) {
    benchmark::DoNotOptimize(ptr3 = ptr2);
    benchmark::DoNotOptimize(ptr2 = ptr1);
    benchmark::DoNotOptimize(ptr1 = ptr3);
  }
}

static void unique_std_swap(benchmark::State& state) {
  auto ptr1 = std::make_unique<std::vector<float>>(100);
  auto ptr2 = std::make_unique<std::vector<float>>(100);
  auto ptr3 = std::make_unique<std::vector<float>>(100);

  for (auto _ : state) {
    benchmark::DoNotOptimize(ptr3 = std::move(ptr2));
    benchmark::DoNotOptimize(ptr2 = std::move(ptr1));
    benchmark::DoNotOptimize(ptr1 = std::move(ptr3));
  }
}

static void unique_cleverptr_swap(benchmark::State& state) {
  auto ptr1 = cleverptr::make_unique<std::vector<float>>(100);
  auto ptr2 = cleverptr::make_unique<std::vector<float>>(100);
  auto ptr3 = cleverptr::make_unique<std::vector<float>>(100);

  for (auto _ : state) {
    benchmark::DoNotOptimize(ptr3 = std::move(ptr2));
    benchmark::DoNotOptimize(ptr2 = std::move(ptr1));
    benchmark::DoNotOptimize(ptr1 = std::move(ptr3));
  }
}

BENCHMARK(shared_std_swap);
BENCHMARK(shared_cleverptr_swap);

BENCHMARK(unique_std_swap);
BENCHMARK(unique_cleverptr_swap);

BENCHMARK_MAIN();

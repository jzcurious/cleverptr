#include "benchmark/benchmark.h"
#include "shared.hpp"
#include "unique.hpp"
#include "weak.hpp"
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

static void weak_std_swap(benchmark::State& state) {
  auto ptr1 = std::make_shared<std::vector<float>>(100);
  auto ptr2 = std::make_shared<std::vector<float>>(100);
  auto ptr3 = std::make_shared<std::vector<float>>(100);
  auto ptr4 = std::weak_ptr(ptr1);
  auto ptr5 = std::weak_ptr(ptr2);
  auto ptr6 = std::weak_ptr(ptr3);

  for (auto _ : state) {
    benchmark::DoNotOptimize(ptr6 = std::move(ptr5));
    benchmark::DoNotOptimize(ptr5 = std::move(ptr4));
    benchmark::DoNotOptimize(ptr4 = std::move(ptr6));
  }
}

static void weak_cleverptr_swap(benchmark::State& state) {
  auto ptr1 = cleverptr::make_shared<std::vector<float>>(100);
  auto ptr2 = cleverptr::make_shared<std::vector<float>>(100);
  auto ptr3 = cleverptr::make_shared<std::vector<float>>(100);
  auto ptr4 = cleverptr::weak_ptr(ptr1);
  auto ptr5 = cleverptr::weak_ptr(ptr2);
  auto ptr6 = cleverptr::weak_ptr(ptr3);

  for (auto _ : state) {
    benchmark::DoNotOptimize(ptr6 = std::move(ptr5));
    benchmark::DoNotOptimize(ptr5 = std::move(ptr4));
    benchmark::DoNotOptimize(ptr4 = std::move(ptr6));
  }
}

BENCHMARK(shared_std_swap);
BENCHMARK(shared_cleverptr_swap);

BENCHMARK(unique_std_swap);
BENCHMARK(unique_cleverptr_swap);

BENCHMARK(weak_std_swap);
BENCHMARK(weak_cleverptr_swap);

BENCHMARK_MAIN();

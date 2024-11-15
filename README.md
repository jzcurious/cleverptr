# cleverptr

An alternative implementation of std smart pointers.

### Benchmark result

Running ./cleverptr-benchmarks\
Run on (16 X 3546.03 MHz CPU s)\
CPU Caches:\
 L1 Data 32 KiB (x8)\
 L1 Instruction 32 KiB (x8)\
 L2 Unified 512 KiB (x8)\
 L3 Unified 16384 KiB (x1)\
 Load Average: 2.38, 1.66, 1.62

Shared:

| Benchmark                    | Time     | CPU      | Iterations |
| ---------------------------- | -------- | -------- | ---------- |
| shared_std_swap_mean         | 7.21 ns  | 7.20 ns  | 4          |
| shared_std_swap_median       | 7.21 ns  | 7.20 ns  | 4          |
| shared_std_swap_stddev       | 0.013 ns | 0.010 ns | 4          |
| shared_std_swap_cv           | 0.18 %   | 0.14 %   | 4          |
| shared_cleverptr_swap_mean   | 2.06 ns  | 2.06 ns  | 4          |
| shared_cleverptr_swap_median | 2.06 ns  | 2.05 ns  | 4          |
| shared_cleverptr_swap_stddev | 0.010 ns | 0.010 ns | 4          |
| shared_cleverptr_swap_cv     | 0.50 %   | 0.51 %   | 4          |

Weak:

| Benchmark                  | Time     | CPU      | Iterations |
| -------------------------- | -------- | -------- | ---------- |
| weak_std_swap_mean         | 3.07 ns  | 3.06 ns  | 4          |
| weak_std_swap_median       | 3.07 ns  | 3.05 ns  | 4          |
| weak_std_swap_stddev       | 0.007 ns | 0.005 ns | 4          |
| weak_std_swap_cv           | 0.22 %   | 0.18 %   | 4          |
| weak_cleverptr_swap_mean   | 3.06 ns  | 3.05 ns  | 4          |
| weak_cleverptr_swap_median | 3.06 ns  | 3.05 ns  | 4          |
| weak_cleverptr_swap_stddev | 0.002 ns | 0.001 ns | 4          |
| weak_cleverptr_swap_cv     | 0.07 %   | 0.03 %   | 4          |

Unique:

Benchmark                       |      Time      |       CPU |  Iterations
--------------------------------|----------------|-----------|------------
unique_std_swap_mean            |   1.62 ns      |   1.61 ns |           4
unique_std_swap_median          |   1.62 ns      |   1.61 ns |           4
unique_std_swap_stddev          |  0.015 ns      |  0.015 ns |           4
unique_std_swap_cv              |   0.94 %       |   0.95 %  |           4
unique_cleverptr_swap_mean      |   1.37 ns      |   1.36 ns |           4
unique_cleverptr_swap_median    |   1.37 ns      |   1.36 ns |           4
unique_cleverptr_swap_stddev    |  0.003 ns      |  0.003 ns |           4
unique_cleverptr_swap_cv        |   0.19 %       |   0.19 %  |           4

_(see benchmarks.cpp)_

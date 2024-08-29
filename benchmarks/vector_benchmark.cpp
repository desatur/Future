#include <benchmark/benchmark.h>
#include "../src/Structs/Vector2.h"
#include "../src/Structs/Vector3.h"

// Example benchmark for Vector2
static void BM_Vector2_Addition(benchmark::State& state) {
    Vector2 a(1.0f, 2.0f);
    Vector2 b(3.0f, 4.0f);
    for (auto _ : state) {
        benchmark::DoNotOptimize(a + b);
    }
}
BENCHMARK(BM_Vector2_Addition);

// Example benchmark for Vector3
static void BM_Vector3_Addition(benchmark::State& state) {
    Vector3 a(1.0f, 2.0f, 3.0f);
    Vector3 b(4.0f, 5.0f, 6.0f);
    for (auto _ : state) {
        benchmark::DoNotOptimize(a + b);
    }
}
BENCHMARK(BM_Vector3_Addition);

// Main function to run benchmarks
BENCHMARK_MAIN();

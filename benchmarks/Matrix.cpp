#include "math/Matrix.hpp"

#include <benchmark/benchmark.h>
#include <random>
#include <vector>

#include "common/Generators.hpp"
#include "math/Strassen.hpp"


namespace Algorithms::Benchmarks
{
    static void BM_StandardMultiply(benchmark::State& state)
    {
        size_t n = state.range(0);
        auto a = Common::CreateRandomMatrix<double>(n, n); 
        auto b = Common::CreateRandomMatrix<double>(n, n);

        for (auto _ : state)
        {
            Math::Matrix<double> res = a * b;
            benchmark::DoNotOptimize(res);
        }
        state.SetComplexityN(n);
    }

    static void BM_StrassenMultiply(benchmark::State& state)
    {
        size_t n = state.range(0);
        auto a = Common::CreateRandomMatrix<double>(n, n);
        auto b = Common::CreateRandomMatrix<double>(n, n);

        for (auto _ : state)
        {
            Math::Matrix<double> res = Math::Strassen<double>::Multiply(a, b);
            benchmark::DoNotOptimize(res);
        }
        state.SetComplexityN(n);
    }

    BENCHMARK(BM_StandardMultiply)
        ->RangeMultiplier(2)
        ->Range(64, 1024)
        ->Complexity(benchmark::oNCubed)
        ->Unit(benchmark::kMillisecond);

    BENCHMARK(BM_StrassenMultiply)
        ->RangeMultiplier(2)
        ->Range(64, 1024)
        ->Complexity([](benchmark::IterationCount n) -> double
            { return std::pow(static_cast<double>(n), 2.81); })
        ->Unit(benchmark::kMillisecond);
}
#include <benchmark/benchmark.h>
#include <vector>

#include "common/Generators.hpp"
#include "sorting/HeapSort.hpp"
#include "sorting/InsertionSort.hpp"
#include "sorting/LinearSorts.hpp"
#include "sorting/MergeSort.hpp"
#include "sorting/QuickSorts.hpp"


namespace Algorithms::Benchmarks
{
    enum class Distribution
    {
        Random,
        Sorted,
        ReverseSorted
    };

    template <typename Algo, Distribution Dist>
    static void BM_SortingBenchmark(benchmark::State& state)
    {
        const size_t size = state.range(0);
        std::vector<int> masterData;
        if constexpr (Dist == Distribution::Random)
            masterData = Common::GenerateRandom(size);
        else if constexpr (Dist == Distribution::Sorted)
            masterData = Common::GenerateSorted(size);
        else if constexpr (Dist == Distribution::ReverseSorted)
            masterData = Common::GenerateReverse(size);

        Algo algo;
        std::vector<int> data(size);
        for (auto _ : state)
        {
            std::copy(masterData.begin(), masterData.end(), data.begin());
            std::invoke(algo, data);
            benchmark::DoNotOptimize(data.data());
        }

        state.SetComplexityN(size);
    }

    BENCHMARK_TEMPLATE(
        BM_SortingBenchmark, Algorithms::Sorting::InsertionSort, Distribution::Random)
        ->Name("BM_InsertionSort/Random")
        ->RangeMultiplier(2)
        ->Range(8, 4096)
        ->Complexity(benchmark::oNSquared);

    BENCHMARK_TEMPLATE(
        BM_SortingBenchmark, Algorithms::Sorting::InsertionSort, Distribution::Sorted)
        ->Name("BM_InsertionSort/Sorted")
        ->RangeMultiplier(2)
        ->Range(8, 4096)
        ->Complexity(benchmark::oN);

    BENCHMARK_TEMPLATE(
        BM_SortingBenchmark, Algorithms::Sorting::InsertionSort, Distribution::ReverseSorted)
        ->Name("BM_InsertionSort/Reverse")
        ->RangeMultiplier(2)
        ->Range(8, 4096)
        ->Complexity(benchmark::oNSquared);

    BENCHMARK_TEMPLATE(BM_SortingBenchmark, Algorithms::Sorting::MergeSort, Distribution::Random)
        ->Name("BM_MergeSort/Random")
        ->RangeMultiplier(2)
        ->Range(8, 4096)
        ->Complexity(benchmark::oNLogN);

    BENCHMARK_TEMPLATE(BM_SortingBenchmark, Algorithms::Sorting::MergeSort, Distribution::Sorted)
        ->Name("BM_MergeSort/Sorted")
        ->RangeMultiplier(2)
        ->Range(8, 4096)
        ->Complexity(benchmark::oNLogN);

    BENCHMARK_TEMPLATE(
        BM_SortingBenchmark, Algorithms::Sorting::MergeSort, Distribution::ReverseSorted)
        ->Name("BM_MergeSort/Reverse")
        ->RangeMultiplier(2)
        ->Range(8, 4096)
        ->Complexity(benchmark::oNLogN);

    BENCHMARK_TEMPLATE(BM_SortingBenchmark, Algorithms::Sorting::HeapSort, Distribution::Random)
        ->Name("BM_HeapSort/Random")
        ->RangeMultiplier(2)
        ->Range(8, 4096)
        ->Complexity(benchmark::oNLogN);

    BENCHMARK_TEMPLATE(BM_SortingBenchmark, Algorithms::Sorting::HeapSort, Distribution::Sorted)
        ->Name("BM_HeapSort/Sorted")
        ->RangeMultiplier(2)
        ->Range(8, 4096)
        ->Complexity(benchmark::oNLogN);

    BENCHMARK_TEMPLATE(
        BM_SortingBenchmark, Algorithms::Sorting::HeapSort, Distribution::ReverseSorted)
        ->Name("BM_HeapSort/Reverse")
        ->RangeMultiplier(2)
        ->Range(8, 4096)
        ->Complexity(benchmark::oNLogN);

    BENCHMARK_TEMPLATE(BM_SortingBenchmark, Algorithms::Sorting::QuickSort, Distribution::Random)
        ->Name("BM_QuickSort/Random")
        ->RangeMultiplier(2)
        ->Range(8, 4096)
        ->Complexity(benchmark::oNLogN);

    BENCHMARK_TEMPLATE(BM_SortingBenchmark, Algorithms::Sorting::QuickSort, Distribution::Sorted)
        ->Name("BM_QuickSort/Sorted")
        ->RangeMultiplier(2)
        ->Range(8, 4096)
        ->Complexity(benchmark::oNSquared);

    BENCHMARK_TEMPLATE(
        BM_SortingBenchmark, Algorithms::Sorting::QuickSort, Distribution::ReverseSorted)
        ->Name("BM_QuickSort/Reverse")
        ->RangeMultiplier(2)
        ->Range(8, 4096)
        ->Complexity(benchmark::oNSquared);

    BENCHMARK_TEMPLATE(
        BM_SortingBenchmark, Algorithms::Sorting::RandomizedQuickSort, Distribution::Random)
        ->Name("BM_RandomizedQuickSort/Random")
        ->RangeMultiplier(2)
        ->Range(8, 4096)
        ->Complexity(benchmark::oNLogN);

    BENCHMARK_TEMPLATE(
        BM_SortingBenchmark, Algorithms::Sorting::RandomizedQuickSort, Distribution::Sorted)
        ->Name("BM_RandomizedQuickSort/Sorted")
        ->RangeMultiplier(2)
        ->Range(8, 4096)
        ->Complexity(benchmark::oNLogN);

    BENCHMARK_TEMPLATE(
        BM_SortingBenchmark, Algorithms::Sorting::RandomizedQuickSort, Distribution::ReverseSorted)
        ->Name("BM_RandomizedQuickSort/Reverse")
        ->RangeMultiplier(2)
        ->Range(8, 4096)
        ->Complexity(benchmark::oNLogN);

    // Линейные
    BENCHMARK_TEMPLATE(BM_SortingBenchmark, Algorithms::Sorting::RadixSort, Distribution::Random)
        ->Name("BM_RadixSort/Random")
        ->RangeMultiplier(2)
        ->Range(8, 4096)
        ->Complexity(benchmark::oN);

    BENCHMARK_TEMPLATE(BM_SortingBenchmark, Algorithms::Sorting::RadixSort, Distribution::Sorted)
        ->Name("BM_RadixSort/Sorted")
        ->RangeMultiplier(2)
        ->Range(8, 4096)
        ->Complexity(benchmark::oN);

    BENCHMARK_TEMPLATE(
        BM_SortingBenchmark, Algorithms::Sorting::RadixSort, Distribution::ReverseSorted)
        ->Name("BM_RadixSort/Reverse")
        ->RangeMultiplier(2)
        ->Range(8, 4096)
        ->Complexity(benchmark::oN);
}
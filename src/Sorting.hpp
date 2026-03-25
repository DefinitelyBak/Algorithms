#include <benchmark/benchmark.h>
#include <vector>
#include <algorithm>
#include <random>

namespace Algorithm::Sorting {
    void InsertionSort(std::vector<int>& arr);
}

// Генератор данных
enum class Distribution { Random, Sorted, ReverseSorted };

std::vector<int> CreateData(size_t size, Distribution dist) {
    std::vector<int> data(size);
    std::iota(data.begin(), data.end(), 0); // Заполняем 0, 1, 2...
    
    if (dist == Distribution::Random) {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(data.begin(), data.end(), g);
    } else if (dist == Distribution::ReverseSorted) {
        std::reverse(data.begin(), data.end());
    }
    return data;
}

// Основной шаблон бенчмарка
static void BM_InsertionSort(benchmark::State& state, Distribution dist) {
    const size_t size = state.range(0);
    auto master_data = CreateData(size, dist);

    for (auto _ : state) {
        state.PauseTiming();   // Останавливаем таймер
        std::vector<int> data = master_data; // Копируем данные для чистоты теста
        state.ResumeTiming();  // Запускаем таймер

        Algorithm::Sorting::InsertionSort(data);
        
        benchmark::DoNotOptimize(data.data());
    }
    
    // Указываем количество обработанных элементов для расчета сложности O(N)
    state.SetComplexityN(state.range(0));
}

// Регистрация бенчмарков для разных случаев
BENCHMARK_CAPTURE(BM_InsertionSort, Random, Distribution::Random)
    ->RangeMultiplier(2)->Range(8, 4096)
    ->Complexity(benchmark::oNSquared);

BENCHMARK_CAPTURE(BM_InsertionSort, Sorted, Distribution::Sorted)
    ->RangeMultiplier(2)->Range(8, 4096)
    ->Complexity(benchmark::oN);

BENCHMARK_CAPTURE(BM_InsertionSort, Reverse, Distribution::ReverseSorted)
    ->RangeMultiplier(2)->Range(8, 4096)
    ->Complexity(benchmark::oNSquared);

BENCHMARK_MAIN();
#include <benchmark/benchmark.h>
#include <string>
#include <cstring>
#include <memory>

// 1. Создание пустой строки
static void BM_StringCreation(benchmark::State& state) {
  for (auto _ : state) {
    std::string empty_string;
    // Заставляем компилятор думать, что строка используется
    benchmark::DoNotOptimize(empty_string);
  }
}
BENCHMARK(BM_StringCreation);

// 2. Копирование строки
static void BM_StringCopy(benchmark::State& state) {
  std::string x = "hello";
  for (auto _ : state) {
    std::string copy(x);
    // Заставляем компилятор думать, что копия используется
    benchmark::DoNotOptimize(copy);
  }
}
BENCHMARK(BM_StringCopy);

// 3. Копирование памяти (memcpy)
static void BM_memcpy(benchmark::State& state) {
  const size_t size = state.range(0);
  char* src = new char[size];
  char* dst = new char[size];
  std::memset(src, 'x', size);

  for (auto _ : state) {
    std::memcpy(dst, src, size);
    
    // DoNotOptimize(dst) говорит, что результат memcpy нам важен
    benchmark::DoNotOptimize(dst);
    // ClobberMemory заставляет компилятор реально записывать данные в память,
    // а не оптимизировать работу через регистры процессора
    benchmark::ClobberMemory();
  }

  state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(size));
  delete[] src;
  delete[] dst;
}
BENCHMARK(BM_memcpy)->Arg(8)->Arg(64)->Arg(512)->Arg(4<<10)->Arg(8<<10);

static void BM_StringCompare(benchmark::State& state) {
  std::string s1(state.range(0), '-');
  std::string s2(state.range(0), '-');
  for (auto _ : state) {
    auto comparison_result = s1.compare(s2);
    benchmark::DoNotOptimize(comparison_result);
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_StringCompare)
    ->RangeMultiplier(2)->Range(1<<10, 1<<18)->Complexity(benchmark::oN);
#include "Generators.hpp"

#include <algorithm>
#include <random>


namespace Algorithms::Benchmarks::Common
{
    std::vector<int> GenerateRandom(size_t n)
    {
        std::vector<int> data(n);
        std::iota(data.begin(), data.end(), 0);
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(data.begin(), data.end(), g);
        return data;
    }

    std::vector<int> GenerateSorted(size_t n)
    {
        std::vector<int> result(n);
        std::iota(result.begin(), result.end(), 0);
        return result;
    }

    std::vector<int> GenerateReverse(size_t n)
    {
        std::vector<int> result = GenerateSorted(n);
        std::reverse(result.begin(), result.end());
        return result;
    }
}
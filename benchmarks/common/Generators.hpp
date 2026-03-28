#pragma once

#include <vector>


namespace Algorithms::Benchmarks::Common
{
    std::vector<int> GenerateRandom(size_t n);
    std::vector<int> GenerateSorted(size_t n);
    std::vector<int> GenerateReverse(size_t n);
}
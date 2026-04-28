#pragma once

#include <vector>

#include "math/Matrix.hpp"


namespace Algorithms::Benchmarks::Common
{
    std::vector<int> GenerateRandom(size_t n);
    std::vector<int> GenerateSorted(size_t n);
    std::vector<int> GenerateReverse(size_t n);
    Math::Matrix<double> CreateRandomMatrix(size_t rows, size_t cols);
}
#pragma once

#include "math/Matrix.hpp"
#include "structures/Vector.hpp"


namespace Algorithms::Benchmarks::Common
{
    Structures::Vector<int> GenerateRandom(size_t n);
    Structures::Vector<int> GenerateSorted(size_t n);
    Structures::Vector<int> GenerateReverse(size_t n);
    Math::Matrix<double> CreateRandomMatrix(size_t rows, size_t cols);
}
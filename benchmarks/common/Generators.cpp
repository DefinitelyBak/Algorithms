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

    Math::Matrix<double> CreateRandomMatrix(size_t rows, size_t cols)
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(1.0, 10.0);

        Math::Matrix<double> m(rows, cols);
        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < cols; ++j)
                m(i, j) = dis(gen);
        return m;
    }
}
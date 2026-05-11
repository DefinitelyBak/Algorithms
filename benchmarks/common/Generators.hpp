#pragma once

#include <algorithm>
#include <concepts>
#include <random>

#include "math/Matrix.hpp"
#include "structures/Vector.hpp"


namespace Algorithms::Benchmarks::Common
{
    static std::mt19937& GetGenerator()
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        return gen;
    }

    template <typename T>
        requires std::is_arithmetic_v<T>
    Structures::Vector<T> GenerateRandom(size_t n)
    {
        Structures::Vector<T> data(n);
        auto& gen = GetGenerator();

        if constexpr (std::is_integral_v<T>)
        {
            std::uniform_int_distribution<long long> dis(
                std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
            for (auto& val : data)
                val = static_cast<T>(dis(gen));
        }
        else
        {
            std::uniform_real_distribution<T> dis(0, 1);
            for (auto& val : data)
                val = dis(gen);
        }
        return data;
    }
    template <typename T>
        requires std::is_arithmetic_v<T>
    Structures::Vector<T> GenerateSorted(size_t n)
    {
        Structures::Vector<T> result(n);
        for (size_t i = 0; i < n; ++i)
            result[i] = static_cast<T>(i);
        return result;
    }
    template <typename T>
        requires std::is_arithmetic_v<T>
    Structures::Vector<T> GenerateReverse(size_t n)
    {
        Structures::Vector<T> result = GenerateSorted<T>(n);
        std::reverse(result.begin(), result.end());
        return result;
    }

    template <typename T>
        requires std::is_arithmetic_v<T>
    Math::Matrix<T> CreateRandomMatrix(size_t rows, size_t cols, T min = 0, T max = 10)
    {
        auto& gen = GetGenerator();
        Math::Matrix<T> m(rows, cols);

        if constexpr (std::is_integral_v<T>)
        {
            std::uniform_int_distribution<long long> dis(
                static_cast<long long>(min), static_cast<long long>(max));
            for (size_t i = 0; i < rows; ++i)
                for (size_t j = 0; j < cols; ++j)
                    m(i, j) = static_cast<T>(dis(gen));
        }
        else
        {
            std::uniform_real_distribution<T> dis(min, max);
            for (size_t i = 0; i < rows; ++i)
                for (size_t j = 0; j < cols; ++j)
                    m(i, j) = dis(gen);
        }
        return m;
    }
}
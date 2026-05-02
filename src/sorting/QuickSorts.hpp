#pragma once

#include <cstddef>
#include <random>
#include <vector>

#include "Common.hpp"


namespace Algorithms::Sorting
{
    struct QuickSort
    {
        template <typename T, typename Compare = std::less<T>>
        void operator()(std::vector<T>& array, Compare comp = Compare()) noexcept
        {
            quickSort<T, Compare>(array, 0, array.size() - 1, comp);
        }

    private:
        template <typename T, typename Compare = std::less<T>>
        void quickSort(std::vector<T>& array, int64_t p, int64_t r, Compare& comp)
        {
            if (p < r)
            {
                const int64_t q = Auxiliary::Partition<T, Compare>(array, p, r, comp);
                quickSort<T, Compare>(array, p, q - 1, comp);
                quickSort<T, Compare>(array, q + 1, r, comp);
            }
        }
    };

    struct RandomizedQuickSort
    {
        template <typename T, typename Compare = std::less<T>>
        void operator()(std::vector<T>& array, Compare comp = Compare()) noexcept
        {
            randomizedQuickSort<T, Compare>(array, 0, array.size() - 1, comp);
        }

    private:
        template <typename T, typename Compare = std::less<T>>
        void randomizedQuickSort(std::vector<T>& array, int64_t p, int64_t r, Compare& comp)
        {
            if (p < r)
            {
                const int64_t q = Auxiliary::RandomizedPartition<T, Compare>(array, p, r, _gen, comp);
                randomizedQuickSort<T, Compare>(array, p, q - 1, comp);
                randomizedQuickSort<T, Compare>(array, q + 1, r, comp);
            }
        }

        std::mt19937 _gen{std::random_device{}()};
    };
}  // namespace Algorithms::Sorting
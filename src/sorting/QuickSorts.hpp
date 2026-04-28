#pragma once

#include <cstddef>
#include <random>
#include <vector>


namespace Algorithms::Sorting
{
    struct QuickSort
    {
        template <typename T, typename Compare = std::less<T>>
        void operator()(std::vector<T>& array, Compare comp = Compare()) noexcept
        {
            quickSort<T, Compare>(array, 0, array.size() - 1, comp);
        }

    protected:
        template <typename T, typename Compare = std::less<T>>
        int64_t partition(std::vector<T>& array, int64_t p, int64_t r, Compare& comp)
        {
            T pivot = array[r];
            int64_t i = p - 1;
            for (int64_t j = p; j < r; ++j)
            {
                if (comp(array[j], pivot))
                {
                    ++i;
                    std::swap(array[i], array[j]);
                }
            }
            std::swap(array[i + 1], array[r]);
            return i + 1;
        }

    private:
        template <typename T, typename Compare = std::less<T>>
        void quickSort(std::vector<T>& array, int64_t p, int64_t r, Compare& comp)
        {
            if (p < r)
            {
                const int64_t q = partition<T, Compare>(array, p, r, comp);
                quickSort<T, Compare>(array, p, q - 1, comp);
                quickSort<T, Compare>(array, q + 1, r, comp);
            }
        }
    };

    struct RandomizedQuickSort final: QuickSort
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
                const int64_t q = randomizedPartition<T, Compare>(array, p, r, comp);
                randomizedQuickSort<T, Compare>(array, p, q - 1, comp);
                randomizedQuickSort<T, Compare>(array, q + 1, r, comp);
            }
        }

        template <typename T, typename Compare = std::less<T>>
        int64_t randomizedPartition(std::vector<T>& array, int64_t p, int64_t r, Compare& comp)
        {
            int64_t range = r - p + 1;
            int64_t pivotIndex = p + (static_cast<int64_t>(_gen()) % range); 
            std::swap(array[pivotIndex], array[r]);
            return QuickSort::partition(array, p, r, comp);
        }

        std::mt19937 _gen{std::random_device{}()};
    };
}
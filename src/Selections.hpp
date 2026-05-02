#pragma once

#include <cstdint>
#include <functional>
#include <random>
#include <span>
#include <vector>

#include "Common.hpp"


namespace Algorithms::Selection
{
    struct RandomizedSelect
    {
        template <typename T, typename Compare = std::less<T>>
        T operator()(std::vector<T>& array, size_t i, Compare comp = Compare())
        {
            if (array.empty() || i == 0 || i > array.size())
                return T{};
            return select(array, 0, static_cast<int64_t>(array.size()) - 1, i, comp);
        }

    private:
        template <typename T, typename Compare>
        T select(std::vector<T>& array, int64_t p, int64_t r, size_t i, Compare comp)
        {
            if (p == r)
                return array[p];
            const int64_t q = Auxiliary::RandomizedPartition(array, p, r, _gen, comp);
            const int64_t k = q - p + 1;

            if (i == static_cast<size_t>(k))
                return array[q];
            else if (i < static_cast<size_t>(k))
                return select(array, p, q - 1, i, comp);
            else
                return select(array, q + 1, r, i - k, comp);
        }

        std::mt19937 _gen{std::random_device{}()};
    };

    struct Select
    {
        template <typename T, typename Compare = std::less<T>>
        T operator()(std::vector<T>& array, size_t i, Compare comp = Compare()) const
        {
            if (array.empty() || i == 0 || i > array.size())
                return T{};

            return selectImpl(std::span<T>(array), i, comp);
        }

    private:
        template <typename T, typename Compare>
        T selectImpl(std::span<T> array, size_t i, Compare comp) const
        {
            if (array.size() <= 5)
            {
                std::sort(array.begin(), array.end(), comp);
                return array[i - 1];
            }

            size_t numMedians = 0;
            for (size_t j = 0; j < array.size(); j += 5)
            {
                auto groupStart = array.begin() + j;
                auto groupEnd = (j + 5 > array.size()) ? array.end() : groupStart + 5;
                std::sort(groupStart, groupEnd, comp);
                size_t groupSize = std::distance(groupStart, groupEnd);
                std::swap(array[numMedians], *(groupStart + groupSize / 2));
                numMedians++;
            }

            T pivotValue = selectImpl(array.subspan(0, numMedians), (numMedians + 1) / 2, comp);
            auto [qLow, qHigh] = Auxiliary::PartitionAround(array, pivotValue, comp);

            size_t kLow = qLow + 1;
            size_t kHigh = qHigh;

            if (i >= kLow && i <= kHigh)
                return array[qLow];
            else if (i < kLow)
                return selectImpl(array.subspan(0, qLow), i, comp);
            else
                return selectImpl(array.subspan(qHigh), i - kHigh, comp);
        }
    };
}  // Algorithms::Selection
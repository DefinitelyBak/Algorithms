#pragma once

#include <cstddef>
#include <random>

#include "Common.hpp"


namespace Algorithms::Sorting
{
    struct QuickSort
    {
        template <std::bidirectional_iterator Iterator,
            typename Compare = std::less<std::iter_value_t<Iterator>>>
        void operator()(Iterator begin, Iterator end, Compare comp = Compare()) const noexcept
        {
            quickSort(begin, end, comp);
        }

    private:
        template <std::bidirectional_iterator Iterator,
            typename Compare = std::less<std::iter_value_t<Iterator>>>
        void quickSort(Iterator begin, Iterator end, Compare& comp) const noexcept
        {
            if (begin == end || std::next(begin) == end)
                return;

            const auto q = Auxiliary::Partition(begin, end, comp);
            quickSort(begin, q, comp);
            quickSort(std::next(q), end, comp);
        }
    };

    struct RandomizedQuickSort
    {
        template <std::bidirectional_iterator Iterator,
            typename Compare = std::less<std::iter_value_t<Iterator>>>
        void operator()(Iterator begin, Iterator end, Compare comp = Compare()) noexcept
        {
            randomizedQuickSort(begin, end, comp);
        }

    private:
        template <std::bidirectional_iterator Iterator,
            typename Compare = std::less<std::iter_value_t<Iterator>>>
        void randomizedQuickSort(Iterator begin, Iterator end, Compare& comp)
        {
            if (begin == end || std::next(begin) == end)
                return;

            const auto q = Auxiliary::RandomizedPartition(begin, end, _gen, comp);
            randomizedQuickSort(begin, q, comp);
            randomizedQuickSort(std::next(q), end, comp);
        }

        std::mt19937 _gen{std::random_device{}()};
    };
}  // namespace Algorithms::Sorting
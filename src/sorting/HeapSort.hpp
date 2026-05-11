#pragma once

#include "Common.hpp"


namespace Algorithms::Sorting
{
    struct HeapSort
    {
        template <std::random_access_iterator Iterator,
            typename Compare = std::less<std::iter_value_t<Iterator>>>
        void operator()(Iterator begin, Iterator end, Compare comp = Compare()) const noexcept
        {
            const auto n = std::distance(begin, end);
            if (n < 2)
                return;
            Heap::BuildHeap(begin, end, comp);
            for (size_t i = n; i > 1; --i)
            {
                std::iter_swap(begin, begin + (i - 1));
                Heap::Heapify(begin, 0, i - 1, comp);
            }
        }
    };
}  // namespace Algorithms::Sorting
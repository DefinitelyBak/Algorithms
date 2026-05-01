#pragma once

#include "Common.hpp"


namespace Algorithms::Sorting
{
    struct HeapSort
    {
        template <typename T, typename Compare = std::less<T>>
        void operator()(std::vector<T>& array, Compare comp = Compare()) const noexcept
        {
            Heap::BuildHeap(array, comp);
            for (size_t i = array.size(); i > 1; --i)
            {
                std::swap(array[0], array[i - 1]);
                Heap::Heapify(array, 0, i - 1, comp);
            }
        }
    };
} // namespace Algorithms::Sorting
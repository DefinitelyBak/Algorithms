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
            for (int64_t i = array.size() - 1; i > 0; --i)
            {
                std::swap(array[0], array[i]);
                Heap::Heapify(array, 0, i, comp);
            }
        }
    };
}
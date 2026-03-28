#pragma once

#include <vector>


namespace Algorithms::Sorting
{
    struct InsertionSort
    {
        template <typename T, typename Compare = std::less<T>>
        void operator()(std::vector<T>& array, Compare comp = Compare()) const noexcept
        {
            for (size_t i = 1; i < array.size(); ++i)
            {
                T key = array[i];
                size_t j = i;
                while (j > 0 && comp(key, array[j - 1]))
                {
                    array[j] = array[j - 1];
                    --j;
                }
                array[j] = key;
            }
        }
    };
}
#pragma once

#include <vector>


namespace Algorithms::Sorting
{
    struct MergeSort
    {
        template <typename T, typename Compare = std::less<T>>
        void operator()(std::vector<T>& array, Compare comp = Compare()) const
        {
            std::vector<T> buffer(array.size());
            sort(0, array.size(), array, buffer, comp);
        }

    private:
        template <typename T, typename Compare>
        void sort(size_t start, size_t end, std::vector<T>& array, std::vector<T>& buffer,
            const Compare& comp) const
        {
            if (end - start <= 1)
                return;
            
            size_t mid = start + (end - start) / 2;

            sort(start, mid, array, buffer, comp);
            sort(mid, end, array, buffer, comp);
            merge(start, mid, end, array, buffer, comp);
        }

        template <typename T, typename Compare>
        void merge(size_t start, size_t mid, size_t end, std::vector<T>& array,
            std::vector<T>& buffer, const Compare& comp) const
        {
            size_t i = start, j = mid, k = 0;

            while (i < mid && j < end)
            {
                if (!comp(array[j], array[i]))
                    buffer[k++] = std::move(array[i++]);
                else
                    buffer[k++] = std::move(array[j++]);
            }

            while (i < mid)
                buffer[k++] = std::move(array[i++]);

            while (j < end)
                buffer[k++] = std::move(array[j++]);

            std::move(buffer.begin(), buffer.begin() + k, array.begin() + start);
        }
    };
} // namespace Algorithms::Sorting
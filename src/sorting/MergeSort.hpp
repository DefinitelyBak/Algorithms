#pragma once

#include <algorithm>
#include <iterator>

#include "structures/Vector.hpp"


namespace Algorithms::Sorting
{
    struct MergeSort
    {
        template <std::random_access_iterator Iterator,
            typename Compare = std::less<std::iter_value_t<Iterator>>>
        void operator()(Iterator begin, Iterator end, Compare comp = Compare()) const
        {
            const auto size = std::distance(begin, end);
            if (size <= 1)
                return;

            using ValueType = std::iter_value_t<Iterator>;
            Structures::Vector<ValueType> buffer(size);
            sort(begin, end, buffer.begin(), comp);
        }

    private:
        template <std::random_access_iterator Iterator, typename Compare>
        void sort(Iterator begin, Iterator end, Iterator bufBegin, const Compare& comp) const
        {
            const auto size = std::distance(begin, end);
            if (size <= 1)
                return;

            const auto mid = begin + size / 2;
            const auto buf_mid = bufBegin + size / 2;

            sort(begin, mid, bufBegin, comp);
            sort(mid, end, buf_mid, comp);
            merge(begin, mid, end, bufBegin, comp);
        }

        template <std::random_access_iterator Iterator, typename Compare>
        void merge(Iterator begin, Iterator mid, Iterator end, Iterator bufBegin,
            const Compare& comp) const
        {
            auto left = begin;
            auto right = mid;
            auto it = bufBegin;

            while (left < mid && right < end)
            {
                if (comp(*right, *left))
                    *it++ = std::move(*right++);
                else
                    *it++ = std::move(*left++);
            }

            while (left < mid)
                *it++ = std::move(*left++);
            while (right < end)
                *it++ = std::move(*right++);
            std::move(bufBegin, it, begin);
        }
    };
}  // namespace Algorithms::Sorting
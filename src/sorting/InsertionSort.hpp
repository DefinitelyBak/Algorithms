#pragma once

#include <vector>


namespace Algorithms::Sorting
{
    struct InsertionSort
    {
        template <std::bidirectional_iterator Iterator,
            typename Compare = std::less<std::iter_value_t<Iterator>>>
        void operator()(Iterator begin, Iterator end, Compare comp = Compare()) const
        {
            if (begin == end)
                return;

            for (auto it = std::next(begin); it != end; ++it)
            {
                auto key = std::move(*it);
                auto jt = it;

                while (jt != begin && comp(key, *std::prev(jt)))
                {
                    *jt = std::move(*std::prev(jt));
                    --jt;
                }
                *jt = std::move(key);
            }
        }
    };
}  // namespace Algorithms::Sorting
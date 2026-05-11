#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <random>
#include <span>
#include <utility>
#include <vector>


namespace Algorithms
{
    namespace Auxiliary
    {
        template <std::bidirectional_iterator Iterator,
            typename Compare = std::less<std::iter_value_t<Iterator>>>
        Iterator Partition(Iterator begin, Iterator end, Compare comp = Compare{})
        {
            if (begin == end || std::next(begin) == end)
                return begin;

            auto pivotIt = std::prev(end);
            const auto& pivot = *pivotIt;
            auto i = begin;
            for (auto j = begin; j != pivotIt; ++j)
            {
                if (comp(*j, pivot))
                {
                    std::iter_swap(i, j);
                    ++i;
                }
            }
            std::iter_swap(i, pivotIt);
            return i;
        }

        template <std::bidirectional_iterator Iterator,
            typename Compare = std::less<std::iter_value_t<Iterator>>>
        Iterator RandomizedPartition(Iterator begin, Iterator end, std::mt19937& gen, Compare comp)
        {
            if (begin == end || std::next(begin) == end)
                return begin;
            auto n = std::distance(begin, end);
            std::uniform_int_distribution<std::iter_difference_t<Iterator>> dist(0, n - 1);

            auto pivotIt = std::next(begin, dist(gen));
            std::iter_swap(pivotIt, std::prev(end));
            return Partition(begin, end, comp);
        }

        template <std::bidirectional_iterator Iterator,
            typename Compare = std::less<std::iter_value_t<Iterator>>>
        std::pair<Iterator, Iterator> PartitionAround(
            Iterator begin, Iterator end, const Iterator pivotIt, Compare comp = Compare{})
        {
            if (begin == end)
                return {begin, begin};

            const auto pivot = *pivotIt;
            auto lt = begin;
            auto gt = end;
            auto i = begin;

            while (i != gt)
            {
                if (comp(*i, pivot))
                {
                    std::iter_swap(lt, i);
                    ++lt;
                    ++i;
                }
                else if (comp(pivot, *i))
                {
                    --gt;
                    std::iter_swap(i, gt);
                }
                else
                    ++i;
            }
            return {lt, gt};
        }
    }  // namespace Auxiliary

    namespace Heap
    {
        inline size_t Parent(size_t index) { return (index - 1) / 2; }
        inline size_t LeftChild(size_t index) { return index * 2 + 1; }
        inline size_t RightChild(size_t index) { return index * 2 + 2; }

        template <std::random_access_iterator Iterator,
            typename Compare = std::less<std::iter_value_t<Iterator>>>
        void Heapify(Iterator begin, size_t index, size_t heapSize, Compare comp = Compare{})
        {
            while (true)
            {
                size_t l = LeftChild(index);
                size_t r = RightChild(index);
                size_t interest = index;

                if (l < heapSize && comp(begin[interest], begin[l]))
                    interest = l;
                if (r < heapSize && comp(begin[interest], begin[r]))
                    interest = r;

                if (interest == index)
                    break;

                std::iter_swap(begin + index, begin + interest);
                index = interest;
            }
        }

        template <std::random_access_iterator Iterator,
            typename Compare = std::less<std::iter_value_t<Iterator>>>
        void BuildHeap(Iterator begin, Iterator end, Compare comp = Compare{})
        {
            const size_t n = std::distance(begin, end);
            if (n < 2)
                return;

            for (int64_t i = static_cast<int64_t>(n) / 2 - 1; i >= 0; --i)
                Heapify(begin, static_cast<size_t>(i), n, comp);
        }

        template <std::random_access_iterator Iterator,
            typename Compare = std::less<std::iter_value_t<Iterator>>>
        void HeapSort(Iterator begin, Iterator end, Compare comp = Compare{})
        {
            BuildHeap(begin, end, comp);
            size_t n = std::distance(begin, end);
            for (size_t i = n - 1; i > 0; --i)
            {
                std::iter_swap(begin, begin + i);
                Heapify(begin, 0, i, comp);
            }
        }
    }  // namespace Heap
}  // namespace Algorithms
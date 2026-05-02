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
        template <typename T, typename Compare = std::less<T>>
        int64_t Partition(std::vector<T>& array, int64_t p, int64_t r, Compare comp)
        {
            const T& pivot = array[r];
            int64_t i = p - 1;
            for (int64_t j = p; j < r; ++j)
            {
                if (comp(array[j], pivot))
                {
                    ++i;
                    std::swap(array[i], array[j]);
                }
            }
            std::swap(array[i + 1], array[r]);
            return i + 1;
        }

        template <typename T, typename Compare = std::less<T>>
        int64_t RandomizedPartition(
            std::vector<T>& array, int64_t p, int64_t r, std::mt19937& gen, Compare comp)
        {
            std::uniform_int_distribution<int64_t> dist(p, r);
            int64_t pivotIndex = dist(gen);

            std::swap(array[pivotIndex], array[r]);
            return Partition(array, p, r, comp);
        }

        template <typename T, typename Compare>
        std::pair<size_t, size_t> PartitionAround(
            std::span<T> array, const T& pivotValue, Compare comp)
        {
            size_t lt = 0;
            size_t gt = array.size();
            size_t i = 0;

            while (i < gt)
            {
                if (comp(array[i], pivotValue))
                    std::swap(array[lt++], array[i++]);
                else if (comp(pivotValue, array[i]))
                    std::swap(array[i], array[--gt]);
                else
                    i++;
            }
            return {lt, gt};
        }
    }  // namespace Auxiliary

    namespace Heap
    {
        inline size_t Parent(size_t index) { return (index - 1) / 2; }
        inline size_t LeftChild(size_t index) { return index * 2 + 1; }
        inline size_t RightChild(size_t index) { return index * 2 + 2; }

        template <typename T, typename Compare = std::less<T>>
        void Heapify(
            std::vector<T>& elements, size_t index, size_t heapSize, Compare comp = Compare())
        {
            while (true)
            {
                size_t l = LeftChild(index);
                size_t r = RightChild(index);
                size_t interest = index;

                if (l < heapSize && comp(elements[interest], elements[l]))
                    interest = l;
                if (r < heapSize && comp(elements[interest], elements[r]))
                    interest = r;

                if (interest == index)
                    break;

                std::swap(elements[index], elements[interest]);
                index = interest;
            }
        }

        template <typename T, typename Compare = std::less<T>>
        void BuildHeap(std::vector<T>& elements, Compare comp = Compare())
        {
            if (elements.size() < 2)
                return;
            const size_t heapSize = elements.size();
            for (int64_t index = static_cast<int64_t>(heapSize) / 2 - 1; index >= 0; --index)
                Heapify(elements, static_cast<size_t>(index), heapSize, comp);
        }
    }  // namespace Heap
}  // namespace Algorithms
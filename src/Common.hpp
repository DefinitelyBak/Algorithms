#pragma once

#include <cstddef>


namespace Algorithms
{
    namespace Heap
    {
        size_t Parent(size_t index) { return (index - 1) / 2; }
        size_t LeftChild(size_t index) { return index * 2 + 1; }
        size_t RightChild(size_t index) { return index * 2 + 2; }

        template <typename T, typename Compare>
        void Heapify(std::vector<T>& elements, size_t index, size_t heapSize, Compare comp = std::less<T>())
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
        };

        template <typename T, typename Compare>
        void BuildHeap(std::vector<T>& elements, Compare comp = std::less<T>())
        {
            if (elements.size() < 2) return;
            const size_t heapSize = elements.size();
            for (int64_t index = heapSize / 2 - 1; index >= 0; --index)
                Heapify(elements, index, heapSize, comp);
        }
    };
}
#include "Sort/Include/QuickSort.h"


namespace Algorithm::Sort
{
    size_t Partition(std::span<int> arr)
    {
        std::swap(arr[0], arr[arr.size()/2]);
        size_t left = 1;
        size_t right = arr.size() - 1;

        while (true)
        {
            while (left <= right && arr[left] <= arr[0])
                ++left;
            while (right >=left  && arr[right] >= arr[0])
                --right;
            
            if (right < left)
                break;

            std::swap(arr[left++], arr[right--]);
        }
        std::swap(arr[0], arr[right]);
        return right;
    }

    void QuickSort(std::span<int> arr)
    {
        if (arr.size() <= 1)
            return;

        size_t q = Partition(arr);
        QuickSort(arr.subspan(0, q));
        QuickSort(arr.subspan(q));
    }

}
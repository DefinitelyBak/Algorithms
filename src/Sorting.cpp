#include "Sorting.hpp"

namespace Algorithm::Sorting
{
    void InsertionSort(std::vector<int> &arr)
    {
        if (arr.empty() || arr.size() == 1)
            return;
        for (size_t i = 1; i < arr.size(); ++i)
            for (size_t j = i; j > 0 && arr[j] < arr[j - 1]; --j)
                std::swap(arr[j], arr[j - 1]);
    }
}
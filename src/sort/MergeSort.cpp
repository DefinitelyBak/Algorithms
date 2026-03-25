#include "Sort/Include/MergeSort.h"


namespace Algorithm::Sort
{
    void MergeSort(std::span<int> arr, std::vector<int>& buffer)
    {
        if (arr.size() <= 1)
            return;
        
        size_t med = arr.size() / 2;
        auto left = arr.subspan(0, med);
        auto right = arr.subspan(med);
        
        MergeSort(left, buffer);
        MergeSort(right, buffer);
        
        // Используем буфер для слияния
        std::copy(arr.begin(), arr.end(), buffer.begin());
        
        size_t i = 0, j = med, k = 0;
        while (i < med && j < arr.size())
        {
            arr[k++] = (buffer[i] <= buffer[j]) ? buffer[i++] : buffer[j++];
        }
        
        while (i < med) arr[k++] = buffer[i++];
        while (j < arr.size()) arr[k++] = buffer[j++];
    }

    // Обертка для вызова
    void MergeSort(std::vector<int>& arr)
    {
        std::vector<int> buffer(arr.size());
        MergeSort(arr, buffer);
    }
}
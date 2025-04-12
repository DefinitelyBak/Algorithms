#pragma once

#include "Precompile.h"


namespace Algorithm::Sort
{
    
    /// @brief 
    /// @param arr 
    void QuickSort(std::span<int> arr);

    /// @brief 
    /// @param arr 
    /// @return 
    size_t Partition(std::span<int> arr);

}
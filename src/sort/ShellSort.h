#pragma once

#include "Precompile.h"
#include "InsertionSort.h"

namespace Algorithm::Sort
{
    /*
    Алгоритм:

    Каждый проход в алгоритме характеризуется смещением h_i, таким,
    что сортируются элементы отстающие друг от друга на h_i позиций.
    Шелл предлагал использовать h_t=N/2, h_t−1=h_t/2, … , h_0 = 1.
    Возможны и другие смещения, но h_0 = 1 всегда.

    Начало.
    Шаг 0. i=t.
    Шаг 1. Разобьем массив на списки элементов, отстающих друг от друга на h_i.
           Таких списков будет h_i.
    Шаг 2. Отсортируем элементы каждого списка сортировкой вставками.
    Шаг 3. Объединим списки обратно в массив. Уменьшим i. Если i
           неотрицательно — вернемся к шагу 1
    Конец.
    */

    void ClassicShellSort(std::vector<int>& arr);

    /// @brief 
    /// @param arr 
    void NaiveShellSort(std::vector<int>& arr);

    /// @brief 
    /// @param arrays 
    /// @return 
    std::vector<int> Merge(const std::vector<std::vector<int>>& arrays);
    
}
#pragma once

#include "Precompile.h"


namespace Algorithm::Sort
{
    /*
    Алгоритм:
    На каждом i-ом шаге алгоритма находим i-ый минимальный элемент и меняем его местами с i-ым элементом в массиве.
    Таким образом будет получен массив, отсортированный по неубыванию. 
    */

    /*
    Вариант 1.
    Будем каждый раз проходить по всем еще не отсортированным элементам, и,
    как только найдем элемент меньше, чем первый из неотсортированных, поменяем их местами.
    Таким образом будет нужно O(n^2) обменов (для каждого i требуется O(n − i) обменов).
    P.S. Можно ещё оптимизировать.
    */
    /// @brief Сортирует выбором
    /// @param arr Входной массив
    void SelectSortVariantOne(std::vector<int>& arr)
    {
        if (arr.empty())
            return;

        for(size_t i = 0; i < arr.size() - 1; ++i)
        {
            int& minValue = arr.at(i);
            for (size_t j = i; j < arr.size(); ++j)
                if (minValue > arr.at(j))
                    std::swap(minValue, arr.at(j));
        }
    } 

    /*
    Вариант 2.
    Второй вариант немного более экономный.
    Здесь мы будем менять местами элементы только 1 раз для каждого i, всего будет нужно O(n) обменов.
    Для этого сначала мы будем проходить по всем еще не отсортированным элементам, искать минимальный,
    и только потом менять местами минимальный и первый из неотсортированных. 
    */
    /// @brief Сортирует выбором
    /// @param arr Входной массив
    void SelectSortVariantTwo(std::vector<int>& arr)
    {
        if (arr.empty())
            return;

        for(size_t i = 0; i < arr.size() - 1; ++i)
        {
            int minValue = arr.at(i);
            int indexMinValue = i;

            for (size_t j = i; j < arr.size(); ++j)
                if(minValue > arr.at(j))
                {
                    minValue = arr.at(j);
                    indexMinValue = j;
                }
            
            std::swap(arr.at(i), arr.at(indexMinValue));
        }
    } 
}
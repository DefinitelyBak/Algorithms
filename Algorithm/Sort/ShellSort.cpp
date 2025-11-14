#include "Sort/Include/ShellSort.h"
#include "Sort/Include/InsertionSort.h"

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

    void ClassicShellSort(std::vector<int>& arr)
    {
        size_t n = arr.size();
        
        // Используем последовательность Кнута (1, 4, 13, 40, 121...)
        int h = 1;
        while (h < n/3)
            h = 3*h + 1;
        
        while (h >= 1)
        {
            // Сортировка вставками с шагом h
            for (int i = h; i < n; i++)
                for (int j = i; j >= h && arr[j] < arr[j-h]; j -= h)
                    std::swap(arr[j], arr[j-h]);
            h /= 3;
        }
    }

    void NaiveShellSort(std::vector<int>& arr)
    {
        if (arr.empty() || arr.size() == 1)
            return;

        int t = 0;
        for (int count = arr.size(); count >>= 2 > 0; ++t)
        ;
        
        int h_t = arr.size()/2;
        while (t > 0)
        {
            std::vector<std::vector<int>> arrays(h_t);

            for (int start = 0; start < h_t; ++start)
                for (int index = start; index < arr.size(); index += h_t)
                    arrays[start].push_back(arr[index]);

            for (auto& array : arrays)
                InsertionSort(array);

            arr = Merge(arrays);
            h_t /= 2;
            --t;
        }
    }

    std::vector<int> Merge(const std::vector<std::vector<int>>& arrays)
    {
        using Element = std::pair<int, size_t>;
        std::priority_queue<Element, std::vector<Element>, std::greater<Element>> pq;
        
        std::vector<size_t> indexes(arrays.size());
        for (size_t i = 0; i < arrays.size(); ++i)
        {
            if (!arrays[i].empty())
            {
                pq.emplace(arrays[i][0], i);
                indexes[i] = 1;
            }
        }
        
        std::vector<int> result;
        while (!pq.empty())
        {
            auto [val, i] = pq.top();
            pq.pop();
            result.push_back(val);
            if (indexes[i] < arrays[i].size())
            {
                pq.emplace(arrays[i][indexes[i]], i);
                indexes[i]++;
            }
        }
        return result;
    }

}
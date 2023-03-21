#pragma once

#include "Precompile.h"


namespace Algorithm::Sort
{
    
    /*
    Алгоритм состоит в повторяющихся проходах по сортируемому массиву.
    На каждой итерации последовательно сравниваются соседние элементы, и,
    если порядок в паре неверный, то элементы меняют местами.
    За каждый проход по массиву как минимум один элемент встает на свое место,
    поэтому необходимо совершить не более n−1 проходов,
    где n размер массива, чтобы отсортировать массив.

    Среднее время рвботы O(n^2). 
    */

    /// @brief Сортирует пузырьком
    /// @param arr Входной массив
    void BubbleSort(std::vector<int>& arr)
    {
        for (size_t i = 0; i < arr.size(); ++i)
            for (size_t j = 0; j < arr.size() - 1; ++j)
                if (arr.at(j) > arr.at(j + 1))
                    std::swap(arr.at(j), arr.at(j + 1));
    }

    /// @brief Сортирует пузырьком с оптимизацией
    /// @param arr Входной массив
    void BubbleSortOptimized(std::vector<int>& arr)
    {
        if (arr.empty())
            return;

        size_t sortedEl = 0;
        bool condition = true;
        while(condition)
        {
            condition = false;
            for(size_t j = 0; j < arr.size() - 1 - sortedEl; ++j)
                if (arr.at(j) > arr.at(j + 1))
                {
                    std::swap(arr.at(j), arr.at(j + 1));
                    condition = true;
                }

            ++sortedEl;
        }
    }

    /// Модификации

    /*
    Сортировка чет-нечет
    https://ru.wikipedia.org/wiki/%D0%A1%D0%BE%D1%80%D1%82%D0%B8%D1%80%D0%BE%D0%B2%D0%BA%D0%B0_%D1%87%D1%91%D1%82-%D0%BD%D0%B5%D1%87%D0%B5%D1%82
    */
    /// @brief Сортирует пузырьком с модификацией
    /// @param arr Входной массив
    /// @remark Преимущество этой сортировки — на нескольких процессорах она выполняется быстрее,
    ///         так как четные и нечетные индексы сортируются параллельно.
    void OddEvenSort(std::vector<int>& arr)
    {
        if (arr.empty())
            return;

        size_t N = arr.size();
	    for (size_t i = 0; i < N; i++)
	        // (i % 2) ? 1 : 0 возвращает 1, если i не четное, 0, если i четное
		    for (size_t j = (i % 2) ? 1 : 0; j + 1 < N; j += 2)
			    if (arr.at(j) > arr.at(j + 1))
				    std::swap(arr.at(j), arr.at(j + 1));
    }

    /*
    Сортировка расческой

    Сортировка расческой (англ. comb sort) — модификация пузырьковой сортировки,
    основанной на сравнении элементов на расстоянии.
    Сложность — O(n^2), но стремится к O(n*log(n)).
    Является самой быстрой квадратичной сортировкой.
    Недостаток — она неустойчива. 
    */
    /// @brief Сортировка расческой
    /// @param arr Входной массив
    void CombSort(std::vector<int>& arr)
    {
        if (arr.empty())
            return;

        const double shrink = 1.3;
        size_t gap = arr.size();
        bool swapped = true;

        while (gap > 1 || swapped)
        {
            // Уменьшаем gap с учетом коэффициента
            gap = static_cast<size_t>(gap / shrink);
            if (gap < 1)
                gap = 1;

            swapped = false;
        
            // Проход по массиву с текущим gap
            for (size_t i = 0; i < arr.size() - gap; ++i)
            {
                if (arr.at(i) > arr.at(i + gap))
                {
                    std::swap(arr.at(i), arr.at(i + gap));
                    swapped = true;
                }
            }
        }
    }

    /*
    Сортировка перемешиванием

    Сортировка перемешиванием, также известная как Шейкерная сортировка — разновидность пузырьковой сортировки,
    сортирующая массив в двух направлениях на каждой итерации.
    В среднем, сортировка перемешиванием работает в два раза быстрее пузырька.
    Сложность — O(n2), но стремится она к O(k⋅n),
    где k — максимальное расстояние элемента в неотсортированном массиве от его позиции в отсортированном массиве. 
    */
    /// @brief Сортировка перемешиванием
    /// @param arr Входной массив
    void ShakerSort(std::vector<int>& arr)
    {
        if (arr.empty())
            return;

        int begin = -1;
        size_t end = arr.size() - 1;
        bool swapped = true;

        while (swapped)
        {
            ++begin;
            swapped = false;

            for (auto i = begin; i < end; ++i)
            {
                if(arr.at(i) > arr.at(i + 1))
                {
                    std::swap(arr.at(i), arr.at(i + 1));
                    swapped = true;
                }
            }

            if (!swapped)
                break;

            --end;
            swapped = false;

            for (auto i = end; i > begin; --i)
            {
                if(arr.at(i) < arr.at(i - 1))
                {
                    std::swap(arr.at(i), arr.at(i - 1));
                    swapped = true;
                }
            }
        }
    }
}

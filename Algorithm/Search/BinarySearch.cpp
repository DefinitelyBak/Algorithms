#include "BinarySearch.h"


namespace Algorithm::Search
{
    /*
    Алгоритм:
    Идея поиска заключается в том, чтобы брать элемент посередине,
    между границами, и сравнивать его с искомым.
    Если искомое больше(в случае правостороннего — не меньше), чем элемент сравнения,
    то сужаем область поиска так, чтобы новая левая граница была равна индексу середины предыдущей области.
    В противном случае присваиваем это значение правой границе.
    Проделываем эту процедуру до тех пор,
    пока правая граница больше левой более чем на 1.

    Инвариант цикла:
    правый индекс не меньше искомого элемента, а левый — строго меньше
    (т.к значение m присваевается левой границе l, только тогда, когда a[m] строго меньше искомого элемента key),
    тогда если r=l+1 (что эквивалентно r−l=1), то понятно,
    что r — самое левое вхождение искомого элемента (так как предыдущие элементы уже меньше искомого элемента)
    В случае правостороннего поиска изменится знак сравнения при сужении границ на a[m]⩽k,
    а возвращаемой переменной станет l.
    */

    int LeftBinarySearch(const std::vector<int>& arr, int value)
    {
        if (arr.empty())
            return -1;

        // Поиск левой границы
        int left = 0;
        int right = arr.size() - 1;
        while (left < right)
        {
            int mid = left + (right - left)/2;
            if (arr.at(mid) < value)
                left = mid + 1;
            else
                right = mid;
        }

        return left;
    }

    int RightBinarySearch(const std::vector<int>& arr, int value)
    {
        if (arr.empty())
            return -1;

        // Поиск правой границы
        int left = 0;
        int right = arr.size() - 1;
        while (left < right)
        {
            int mid = left + (right - left)/2 + 1;  // Смещение вправо
            if (arr.at(mid) > value)
                right = mid - 1;
            else
                left = mid;
        }

        return right;
    }

    /// @brief Алгоритм банарного поиска
    /// @param arr 
    /// @return  
    std::pair<int, int> BinarySearch(const std::vector<int>& arr, int value)
    {
        if (arr.empty())
            return {1, -1};

        // Поиск левой границы
        int left = LeftBinarySearch(arr, value);
        int right = RightBinarySearch(arr, value);

        if (left == -1 || right == -1 ||
            arr.at(left) != value || arr.at(right) != value)
            return {1, -1};

        return {left, right};
    }

}
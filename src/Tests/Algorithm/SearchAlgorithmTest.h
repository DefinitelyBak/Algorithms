#pragma once

#include <gtest/gtest.h>
#include "Precompile.h"


namespace Algorithm::Tests 
{
    template <typename SearchFunc>
    class SearchAlgorithmTest : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
            // Подготовка тестовых данных
            sortedArray = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
            emptyArray = {};
            singleElement = { 42 };
            withDuplicates = { 1, 2, 2, 3, 4, 4, 4, 5 };
            negativeNumbers = { -5, -3, -1, 0, 2, 4 };
        }

        // Тестовые массивы
        std::vector<int> sortedArray;
        std::vector<int> emptyArray;
        std::vector<int> singleElement;
        std::vector<int> withDuplicates;
        std::vector<int> negativeNumbers;

        // Общие тесты для всех алгоритмов поиска
        void TestSearchFunction(SearchFunc searchFunc)
        {
            // Поиск в обычном массиве
            EXPECT_EQ((std::pair<int, int>(3,3)), searchFunc(sortedArray, 4));
            EXPECT_EQ((std::pair<int, int>(0, 0)), searchFunc(sortedArray, 1));
            EXPECT_EQ((std::pair<int, int>(9,9)), searchFunc(sortedArray, 10));
            EXPECT_EQ((std::pair<int, int>(1,-1)), searchFunc(sortedArray, 11)); // Не найден

            // Пустой массив
            EXPECT_EQ((std::pair<int, int>(1,-1)), searchFunc(emptyArray, 42));

            // Массив из одного элемента
            EXPECT_EQ((std::pair<int, int>(0,0)), searchFunc(singleElement, 42));
            EXPECT_EQ((std::pair<int, int>(1,-1)), searchFunc(singleElement, 43));

            // Массив с дубликатами
            EXPECT_EQ((std::pair<int, int>(4,6)), searchFunc(withDuplicates, 4));

            // Отрицательные числа
            EXPECT_EQ((std::pair<int, int>(0, 0)), searchFunc(negativeNumbers, -5));
            EXPECT_EQ((std::pair<int, int>(3,3)), searchFunc(negativeNumbers, 0));
        }
    };
}
#include <gtest/gtest.h>
#include "SortingTest.h"
#include "include/BubbleSort.h"
#include "include/SelectionSort.h"
#include "include/InsertionSort.h"


namespace Algorithm::Sort::Tests
{
    /// Bubble sort and modification
    using BubbleSortTest = SortingTest<decltype(&BubbleSort)>;
    TEST_F(BubbleSortTest, SortsCorrectly)
    {
        TestSorting(BubbleSort);
    }

    using BubbleSortOptimizedTest = SortingTest<decltype(&BubbleSortOptimized)>;
    TEST_F(BubbleSortOptimizedTest, SortsCorrectly)
    {
        TestSorting(BubbleSortOptimized);
    }

    using OddEvenSortTest = SortingTest<decltype(&OddEvenSort)>;
    TEST_F(OddEvenSortTest, SortsCorrectly)
    {
        TestSorting(OddEvenSort);
    }

    using CombSortTest = SortingTest<decltype(&CombSort)>;
    TEST_F(CombSortTest, SortsCorrectly)
    {
        TestSorting(CombSort);
    }

    using ShakerSortTest = SortingTest<decltype(&ShakerSort)>;
    TEST_F(ShakerSortTest, SortsCorrectly)
    {
        TestSorting(ShakerSort);
    }

    /// Selection sort
    using SelectSortVariantOneTest = SortingTest<decltype(&SelectSortVariantOne)>;
    TEST_F(SelectSortVariantOneTest, SortsCorrectly)
    {
        TestSorting(SelectSortVariantOne);
    }

    using SelectSortVariantTwoTest = SortingTest<decltype(&SelectSortVariantTwo)>;
    TEST_F(SelectSortVariantTwoTest, SortsCorrectly)
    {
        TestSorting(SelectSortVariantTwo);
    }

    /// Insertion sort
    using InsertionSortTest = SortingTest<decltype(&InsertionSort)>;
    TEST_F(InsertionSortTest, SortsCorrectly)
    {
        TestSorting(InsertionSort);
    }

}
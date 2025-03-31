#include <gtest/gtest.h>
#include "SortingAlgorithmTest.h"
#include "Sort/include/BubbleSort.h"
#include "Sort/include/SelectionSort.h"
#include "Sort/include/InsertionSort.h"
#include "Sort/Include/ShellSort.h"


namespace Algorithm::Tests
{
    using namespace Algorithm::Sort;

    /// Bubble sort and modification
    using BubbleSortTest = SortingAlgorithmTest<decltype(&BubbleSort)>;
    TEST_F(BubbleSortTest, SortsCorrectly)
    {
        TestSorting(BubbleSort);
    }

    using BubbleSortOptimizedTest = SortingAlgorithmTest<decltype(&BubbleSortOptimized)>;
    TEST_F(BubbleSortOptimizedTest, SortsCorrectly)
    {
        TestSorting(BubbleSortOptimized);
    }

    using OddEvenSortTest = SortingAlgorithmTest<decltype(&OddEvenSort)>;
    TEST_F(OddEvenSortTest, SortsCorrectly)
    {
        TestSorting(OddEvenSort);
    }

    using CombSortTest = SortingAlgorithmTest<decltype(&CombSort)>;
    TEST_F(CombSortTest, SortsCorrectly)
    {
        TestSorting(CombSort);
    }

    using ShakerSortTest = SortingAlgorithmTest<decltype(&ShakerSort)>;
    TEST_F(ShakerSortTest, SortsCorrectly)
    {
        TestSorting(ShakerSort);
    }

    /// Selection sort
    using SelectSortVariantOneTest = SortingAlgorithmTest<decltype(&SelectSortVariantOne)>;
    TEST_F(SelectSortVariantOneTest, SortsCorrectly)
    {
        TestSorting(SelectSortVariantOne);
    }

    using SelectSortVariantTwoTest = SortingAlgorithmTest<decltype(&SelectSortVariantTwo)>;
    TEST_F(SelectSortVariantTwoTest, SortsCorrectly)
    {
        TestSorting(SelectSortVariantTwo);
    }

    /// Insertion sort
    using InsertionSortTest = SortingAlgorithmTest<decltype(&InsertionSort)>;
    TEST_F(InsertionSortTest, SortsCorrectly)
    {
        TestSorting(InsertionSort);
    }

    using BinaryInsertionSortTest = SortingAlgorithmTest<decltype(&BinaryInsertionSort)>;
    TEST_F(BinaryInsertionSortTest, SortsCorrectly)
    {
        TestSorting(BinaryInsertionSort);
    }
    
    using ClassicShellSortTest = SortingAlgorithmTest<decltype(&ClassicShellSort)>;
    TEST_F(ClassicShellSortTest, SortsCorrectly)
    {
        TestSorting(ClassicShellSort);
    }

    using NaiveShellSortTest = SortingAlgorithmTest<decltype(&NaiveShellSort)>;
    TEST_F(NaiveShellSortTest, SortsCorrectly)
    {
        TestSorting(NaiveShellSort);
    }
    
}
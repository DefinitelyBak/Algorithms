#include <gtest/gtest.h>
#include "Algorithm/SortingAlgorithmTest.h"
#include "Sort/include/BubbleSort.h"
#include "Sort/include/SelectionSort.h"
#include "Sort/include/InsertionSort.h"
#include "Sort/Include/ShellSort.h"
#include "Sort/Include/MergeSort.h"
#include "Sort/Include/QuickSort.h"


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
    
    /// Shell sort
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

    /// Merge sort
    using MergeSortTest = SortingAlgorithmTest<decltype(&MergeSort)>;
    TEST_F(MergeSortTest, SortsCorrectly)
    {
        TestSorting(MergeSort);
    }

    /// Quick sort
    using QuickSortTest = SortingAlgorithmTest<decltype(&QuickSort)>;
    TEST_F(QuickSortTest, SortsCorrectly)
    {
        TestSorting(QuickSort);
    }
    
}
#include <gtest/gtest.h>
#include "Algorithm/SearchAlgorithmTest.h"
#include "Search/Include/BinarySearch.h"


namespace Algorithm::Tests
{
    using namespace Algorithm::Search;

    /// Bubble sort and modification
    using BinarySearchTest = SearchAlgorithmTest<decltype(&BinarySearch)>;
    TEST_F(BinarySearchTest, SearchCorrectly)
    {
        TestSearchFunction(BinarySearch);
    }
}
#include <gtest/gtest.h>
#include "Precompile.h"


namespace Algorithm::Sort::Tests 
{
    template <typename SortFunction>
    class SortingAlgorithmTest : public ::testing::Test
    {
    protected:
        void TestSorting(SortFunction sortFunc)
        {
            // Примеры тестовых данных
            std::vector<std::vector<int>> testCases =
            {
                {},
                {1},
                {1, 2, 3, 4, 5},
                {5, 4, 3, 2, 1},
                {3, 1, 4, 1, 5, 9, 2, 6},
                {-1, -2, -3, -4, -5}
            };

            for (auto& arr : testCases)
            {
                auto expected = arr;
                std::sort(expected.begin(), expected.end());

                auto actual = arr;
                sortFunc(actual);

                ASSERT_EQ(expected, actual) << "Test failed for input: " << ::testing::PrintToString(arr);
            }
        }
    };
}
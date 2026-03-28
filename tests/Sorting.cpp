#include <gtest/gtest.h>

#include <vector>

#include "sorting/InsertionSort.hpp"
#include "sorting/MergeSort.hpp"


namespace Algorithms::Tests
{
    struct Item final
    {
        int key;
        int originalIndex;

        bool operator<(const Item& other) const { return key < other.key; }
        bool operator==(const Item& other) const
        {
            return key == other.key && originalIndex == other.originalIndex;
        }
    };

    template <typename T>
    class SortingTest : public ::testing::Test
    {
    protected:
        T sortAlgo;
    };

    using SortTypes =
        ::testing::Types<Algorithms::Sorting::InsertionSort, Algorithms::Sorting::MergeSort>;
    TYPED_TEST_SUITE(SortingTest, SortTypes);

    TYPED_TEST(SortingTest, BasicSort)
    {
        std::vector<int> data = {5, 3, 8, 1, 9, 2};
        std::vector<int> expected = {1, 2, 3, 5, 8, 9};

        this->sortAlgo(data);
        EXPECT_EQ(data, expected);
    }

    TYPED_TEST(SortingTest, EdgeCases)
    {
        std::vector<int> empty = {};
        this->sortAlgo(empty);
        EXPECT_TRUE(empty.empty());

        std::vector<int> single = {42};
        this->sortAlgo(single);
        EXPECT_EQ(single[0], 42);
    }

    TYPED_TEST(SortingTest, Stability)
    {
        std::vector<Item> data = {{1, 0}, {2, 1}, {1, 2}, {3, 3}, {2, 4}, {1, 5}};

        this->sortAlgo(data);

        for (size_t i = 1; i < data.size(); ++i)
        {
            EXPECT_LE(data[i - 1].key, data[i].key);

            if (data[i - 1].key == data[i].key)
                EXPECT_LT(data[i - 1].originalIndex, data[i].originalIndex);
        }
    }

    TYPED_TEST(SortingTest, CustomComparator)
    {
        std::vector<int> data = {1, 2, 3, 4, 5};
        std::vector<int> expected = {5, 4, 3, 2, 1};

        this->sortAlgo(data, std::greater<int>());
        EXPECT_EQ(data, expected);
    }
}
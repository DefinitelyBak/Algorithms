#include <gtest/gtest.h>

#include "structures/Vector.hpp"

#include "sorting/HeapSort.hpp"
#include "sorting/InsertionSort.hpp"
#include "sorting/LinearSorts.hpp"
#include "sorting/MergeSort.hpp"
#include "sorting/QuickSorts.hpp"


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

    using AllSortTypes = ::testing::Types<Algorithms::Sorting::InsertionSort,
        Algorithms::Sorting::MergeSort, Algorithms::Sorting::HeapSort,
        Algorithms::Sorting::QuickSort, Algorithms::Sorting::RandomizedQuickSort>;

    using StableSortTypes =
        ::testing::Types<Algorithms::Sorting::InsertionSort, Algorithms::Sorting::MergeSort>;

    template <typename T>
    class SortingTest : public ::testing::Test
    {
    protected:
        T sortAlgo;
    };

    TYPED_TEST_SUITE(SortingTest, AllSortTypes);

    TYPED_TEST(SortingTest, BasicSort)
    {
        Structures::Vector<int> data = {5, 3, 8, 1, 9, 2};
        Structures::Vector<int> expected = {1, 2, 3, 5, 8, 9};
        this->sortAlgo(data.begin(), data.end());
        EXPECT_EQ(data, expected);
    }

    TYPED_TEST(SortingTest, EdgeCases)
    {
        Structures::Vector<int> empty = {};
        this->sortAlgo(empty.begin(), empty.end());
        EXPECT_TRUE(empty.Empty());
    }

    TYPED_TEST(SortingTest, CustomComparator)
    {
        Structures::Vector<int> data = {1, 2, 3, 4, 5};
        Structures::Vector<int> expected = {5, 4, 3, 2, 1};
        this->sortAlgo(data.begin(), data.end(), std::greater<int>());
        EXPECT_EQ(data, expected);
    }

    template <typename T>
    class StableSortingTest : public SortingTest<T>
    {
    };

    TYPED_TEST_SUITE(StableSortingTest, StableSortTypes);

    TYPED_TEST(StableSortingTest, Stability)
    {
        using Item = Algorithms::Tests::Item;
        Structures::Vector<Item> data = {{1, 0}, {2, 1}, {1, 2}, {3, 3}, {2, 4}, {1, 5}};

        this->sortAlgo(data.begin(), data.end());

        for (size_t i = 1; i < data.Size(); ++i)
        {
            EXPECT_LE(data[i - 1].key, data[i].key);
            if (data[i - 1].key == data[i].key)
                EXPECT_LT(data[i - 1].originalIndex, data[i].originalIndex)
                    << "Stability violated at index " << i << " for key " << data[i].key;
        }
    }
}
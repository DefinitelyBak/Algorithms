#include "structures/Vector.hpp"

#include <gtest/gtest.h>

#include <algorithm>


namespace Algorithms::Structures::Tests
{
    struct Tracker
    {
        static inline int aliveCount = 0;
        int value;
        bool throwOnCopy;

        Tracker(int v = 0, bool t = false) : value(v), throwOnCopy(t) { aliveCount++; }
        Tracker(const Tracker& other) : value(other.value), throwOnCopy(other.throwOnCopy)
        {
            if (throwOnCopy)
                throw std::runtime_error("Copy error");
            aliveCount++;
        }
        Tracker(Tracker&& other) noexcept : value(other.value), throwOnCopy(other.throwOnCopy)
        {
            aliveCount++;
        }
        ~Tracker() { aliveCount--; }
    };

    class VectorTest : public ::testing::Test
    {
    protected:
        void SetUp() override { Tracker::aliveCount = 0; }
    };

    TEST_F(VectorTest, RAIIAndBasics)
    {
        {
            Vector<Tracker> v;
            for (int i = 0; i < 10; ++i)
                v.EmplaceBack(i);
            EXPECT_EQ(v.Size(), 10);
            EXPECT_EQ(Tracker::aliveCount, 10);
            v.Clear();
            EXPECT_EQ(v.Size(), 0);
            EXPECT_EQ(Tracker::aliveCount, 0);
        }
        EXPECT_EQ(Tracker::aliveCount, 0);
    }

    TEST_F(VectorTest, SelfPush)
    {
        Vector<int> v = {1, 2, 3};
        v.Reserve(3);
        v.PushBack(v[0]);
        EXPECT_EQ(v.Size(), 4);
        EXPECT_EQ(v.Back(), 1);
    }

    TEST_F(VectorTest, ExceptionSafety)
    {
        Vector<Tracker> v;
        v.EmplaceBack(1);
        v.EmplaceBack(2);

        Tracker bad(3, true);

        EXPECT_ANY_THROW(v.PushBack(bad));
        EXPECT_EQ(v.Size(), 2);
        EXPECT_EQ(v[0].value, 1);
        EXPECT_EQ(v[1].value, 2);
    }

    TEST_F(VectorTest, MoveSemantics)
    {
        Vector<int> v1 = {1, 2, 3};
        Vector<int> v2 = std::move(v1);

        EXPECT_EQ(v2.Size(), 3);
        EXPECT_EQ(v1.Size(), 0);
        EXPECT_EQ(v1.Data(), nullptr);
    }

    TEST(Vector, iterator)
    {
        Vector<int> v1 = {1, 2, 3, 8, 9, 12, 4, 1};
        std::sort(v1.begin(), v1.end());
        EXPECT_EQ(v1[0], 1);
        EXPECT_EQ(v1[1], 1);
        EXPECT_EQ(v1[2], 2);
        EXPECT_EQ(v1[3], 3);
        EXPECT_EQ(v1[4], 4);
        EXPECT_EQ(v1[5], 8);
        EXPECT_EQ(v1[6], 9);
        EXPECT_EQ(v1[7], 12);
    }
}
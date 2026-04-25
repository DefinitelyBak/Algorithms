#include <gtest/gtest.h>

#include <math/Matrix.hpp>


namespace Algorithms::Tests
{
    TEST(MatrixTests, Addition)
    {
        Math::Matrix<int> a({{1, 2}, {3, 4}});
        Math::Matrix<int> b({{5, 6}, {7, 8}});

        Math::Matrix<int> c = a + b;

        EXPECT_EQ(c(0, 0), 6);
        EXPECT_EQ(c(0, 1), 8);
        EXPECT_EQ(c(1, 0), 10);
        EXPECT_EQ(c(1, 1), 12);
    }

    TEST(MatrixTests, Subtraction)
    {
        Math::Matrix<int> a({{1, 2}, {3, 4}});
        Math::Matrix<int> b({{5, 6}, {7, 8}});

        Math::Matrix<int> c = a - b;

        EXPECT_EQ(c(0, 0), -4);
        EXPECT_EQ(c(0, 1), -4);
        EXPECT_EQ(c(1, 0), -4);
        EXPECT_EQ(c(1, 1), -4);
    }

    TEST(MatrixTests, multiplies)
    {
        Math::Matrix<int> a({{1, 2}, {3, 4}});
        Math::Matrix<int> c = a * 3;

        EXPECT_EQ(c(0, 0), 3);
        EXPECT_EQ(c(0, 1), 6);
        EXPECT_EQ(c(1, 0), 9);
        EXPECT_EQ(c(1, 1), 12);

        c = 3 * a;
        EXPECT_EQ(c(0, 0), 3);
        EXPECT_EQ(c(0, 1), 6);
        EXPECT_EQ(c(1, 0), 9);
        EXPECT_EQ(c(1, 1), 12);
    }

    TEST(MatrixTests, Submatrix)
    {
        Math::Matrix<int> a({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
        auto sub = a.submatrix(0, 0, 2, 2);
        EXPECT_EQ(sub(0, 0), 1);
        EXPECT_EQ(sub(0, 1), 2);
        EXPECT_EQ(sub(1, 0), 4);
        EXPECT_EQ(sub(1, 1), 5);
    }

    TEST(MatrixTests, DifficultSubmatrix)
    {
        Math::Matrix<int> a({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
        auto sub = a.submatrix(0, 0, 2, 2);
        EXPECT_EQ(sub(0, 0), 1);
        EXPECT_EQ(sub(0, 1), 2);
        EXPECT_EQ(sub(1, 0), 4);
        EXPECT_EQ(sub(1, 1), 5);
        
        Math::Matrix<int> b({{1, 2}, {4, 5}});
        Math::Matrix<int> c = sub + b;
        EXPECT_EQ(c(0, 0), 2);
        EXPECT_EQ(c(0, 1), 4);
        EXPECT_EQ(c(1, 0), 8);
        EXPECT_EQ(c(1, 1), 10);
    }
}
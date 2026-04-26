#include <gtest/gtest.h>

#include <math/Matrix.hpp>
#include <math/Strassen.hpp>


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
        Math::Matrix<double> a({{1.0, 2.0}, {3.0, 4.0}});
        Math::Matrix<double> c = a * 3;

        EXPECT_EQ(c(0, 0), 3.);
        EXPECT_EQ(c(0, 1), 6.);
        EXPECT_EQ(c(1, 0), 9.);
        EXPECT_EQ(c(1, 1), 12.);

        c = 3 * a;
        EXPECT_EQ(c(0, 0), 3.);
        EXPECT_EQ(c(0, 1), 6.);
        EXPECT_EQ(c(1, 0), 9.);
        EXPECT_EQ(c(1, 1), 12.);
    }

    TEST(MatrixTests, ComplexExpression)
    {
        Math::Matrix<int> a({{1, 1}, {1, 1}});
        Math::Matrix<int> b({{2, 2}, {2, 2}});
        Math::Matrix<int> c({{3, 3}, {3, 3}});

        Math::Matrix<int> res = (a + b) * 2 - c;

        EXPECT_EQ(res(0, 0), 3);
        EXPECT_EQ(res(1, 1), 3);
    }

    TEST(MatrixTests, Slice)
    {
        Math::Matrix<int> a({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
        auto sub = a.Slice(0, 0, 2, 2);
        EXPECT_EQ(sub(0, 0), 1);
        EXPECT_EQ(sub(0, 1), 2);
        EXPECT_EQ(sub(1, 0), 4);
        EXPECT_EQ(sub(1, 1), 5);
    }

    TEST(MatrixTests, SliceAssignment)
    {
        Math::Matrix<int> a({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
        Math::Matrix<int> b({{10, 10}, {10, 10}});

        auto sub = a.Slice(1, 1, 2, 2);
        sub = b * 5;

        EXPECT_EQ(a(1, 1), 50);
        EXPECT_EQ(a(2, 2), 50);
        EXPECT_EQ(a(0, 0), 1);
    }

    TEST(MatrixTests, NestedSlice)
    {
        Math::Matrix<int> a({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}});

        auto s1 = a.Slice(1, 1, 2, 3);
        auto s2 = s1.Slice(1, 1, 1, 2);

        EXPECT_EQ(s2.Rows(), 1);
        EXPECT_EQ(s2.Cols(), 2);
        EXPECT_EQ(s2(0, 0), 11);
        EXPECT_EQ(s2(0, 1), 12);
    }

    TEST(MatrixTests, MismatchedSizesDeathTest)
    {
        Math::Matrix<int> a(2, 2);
        Math::Matrix<int> b(3, 3);

#ifndef NDEBUG
        EXPECT_DEATH({ auto res = a + b; }, "");
#endif
    }

    TEST(BufferMatrixTests, RawMemoryInteraction)
    {
        int rawData[4] = {1, 2, 3, 4};
        Math::BufferMatrix<int> bm(rawData, 2, 2);

        bm(0, 1) = 10;
        EXPECT_EQ(rawData[1], 10);

        rawData[3] = 40;
        EXPECT_EQ(bm(1, 1), 40);
    }

    TEST(BufferMatrixTests, AssignmentFromExpression)
    {
        Math::Matrix<int> a({{1, 1}, {1, 1}});
        Math::Matrix<int> b({{2, 2}, {2, 2}});

        int resultPtr[4] = {0};
        Math::BufferMatrix<int> target(resultPtr, 2, 2);

        target = (a + b) * 5;

        EXPECT_EQ(resultPtr[0], 15);
        EXPECT_EQ(resultPtr[3], 15);
    }

    TEST(BufferMatrixTests, VectorInterop)
    {
        std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
        Math::BufferMatrix<double> bm(data.data(), 2, 3);

        EXPECT_EQ(bm(1, 0), 4.0);

        bm(1, 2) = 0.0;
        EXPECT_EQ(data[5], 0.0);
    }

    TEST(BufferMatrixTests, SliceOfBuffer)
    {
        int data[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        Math::BufferMatrix<int> bm(data, 3, 3);

        auto sub = bm.Slice(1, 1, 2, 2);

        EXPECT_EQ(sub(0, 0), 5);
        EXPECT_EQ(sub(1, 1), 9);

        sub(0, 0) = 50;
        EXPECT_EQ(data[4], 50);
    }

    TEST(BufferMatrixTests, CopyToMatrix)
    {
        int data[4] = {1, 2, 3, 4};
        Math::BufferMatrix<int> bm(data, 2, 2);

        Math::Matrix<int> m = bm;

        EXPECT_EQ(m(1, 1), 4);

        m(1, 1) = 99;
        EXPECT_EQ(data[3], 4);
    }

    TEST(BufferMatrixTests, FlatteningTypeCheck)
    {
        int data[16];
        Math::BufferMatrix<int> bm(data, 4, 4);

        auto s1 = bm.Slice(0, 0, 3, 3);
        auto s2 = s1.Slice(0, 0, 2, 2);

        bool same_type = std::is_same_v<decltype(s1), decltype(s2)>;
        EXPECT_TRUE(same_type);
    }

    TEST(MatrixMultiplication, SquareMatrices)
    {
        Math::Matrix<int> a({{1, 2}, {3, 4}});
        Math::Matrix<int> b({{5, 6}, {7, 8}});
        Math::Matrix<int> c = a * b;

        EXPECT_EQ(c.Rows(), 2);
        EXPECT_EQ(c.Cols(), 2);
        EXPECT_EQ(c(0, 0), 19);
        EXPECT_EQ(c(0, 1), 22);
        EXPECT_EQ(c(1, 0), 43);
        EXPECT_EQ(c(1, 1), 50);
    }

    TEST(MatrixMultiplication, RectangularMatrices)
    {
        Math::Matrix<int> a({{1, 2, 3}, {4, 5, 6}});
        Math::Matrix<int> b({{7, 8}, {9, 10}, {11, 12}});

        Math::Matrix<int> c = a * b;

        EXPECT_EQ(c.Rows(), 2);
        EXPECT_EQ(c.Cols(), 2);
        EXPECT_EQ(c(0, 0), 58);
        EXPECT_EQ(c(1, 1), 154);
    }

    TEST(MatrixMultiplication, IdentityMatrix)
    {
        Math::Matrix<int> a({{1, 2}, {3, 4}});
        Math::Matrix<int> id({{1, 0}, {0, 1}});

        Math::Matrix<int> c = a * id;

        EXPECT_EQ(c(0, 0), 1);
        EXPECT_EQ(c(0, 1), 2);
        EXPECT_EQ(c(1, 0), 3);
        EXPECT_EQ(c(1, 1), 4);
    }

    TEST(MatrixMultiplication, WithExpressions)
    {
        Math::Matrix<int> a({{1, 1}, {1, 1}});
        Math::Matrix<int> b({{2, 2}, {2, 2}});
        Math::Matrix<int> c({{1, 0}, {0, 1}});

        Math::Matrix<int> res = (a + b) * c;

        EXPECT_EQ(res(0, 0), 3);
        EXPECT_EQ(res(1, 1), 3);
    }

    TEST(MatrixMultiplication, SliceMultiplication)
    {
        Math::Matrix<int> a({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
        Math::Matrix<int> b({{1, 0}, {0, 1}});

        auto sub = a.Slice(0, 0, 2, 2);
        Math::Matrix<int> res = sub * b;

        EXPECT_EQ(res(0, 0), 1);
        EXPECT_EQ(res(1, 1), 5);
    }

    TEST(MatrixMultiplication, DimensionMismatch)
    {
        Math::Matrix<int> a(2, 3);
        Math::Matrix<int> b(2, 3);

#ifndef NDEBUG
        EXPECT_DEATH({ auto res = a * b; }, "");
#endif
    }

    TEST(MatrixMultiplication, Strassen)
    {
        Math::Matrix<int> a({{1, 2}, {3, 4}});
        Math::Matrix<int> b({{5, 6}, {7, 8}});
        Math::Matrix<int> c = Math::Strassen<int>::Multiply(a, b);

        EXPECT_EQ(c.Rows(), 2);
        EXPECT_EQ(c.Cols(), 2);
        EXPECT_EQ(c(0, 0), 19);
        EXPECT_EQ(c(0, 1), 22);
        EXPECT_EQ(c(1, 0), 43);
        EXPECT_EQ(c(1, 1), 50);
    }
}
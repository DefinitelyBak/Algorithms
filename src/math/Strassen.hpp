#pragma once

#include <algorithm>
#include <cassert>
#include <vector>

#include "Matrix.hpp"


namespace Algorithms::Math
{
    template <typename T>
    class Strassen
    {
        static constexpr size_t THRESHOLD = 64;

    public:
        template <MatrixLike Lhs, MatrixLike Rhs>
        static Matrix<T> Multiply(const Lhs& lhs, const Rhs& rhs)
        {
            assert(lhs.Cols() == rhs.Rows());

            size_t rowsA = lhs.Rows();
            size_t colsA = lhs.Cols();
            size_t colsB = rhs.Cols();

            size_t paddedSize = 1;
            size_t maxDim = std::max({rowsA, colsA, colsB});
            while (paddedSize < maxDim)
                paddedSize *= 2;

            Matrix<T> paddedA(paddedSize, paddedSize);
            Matrix<T> paddedB(paddedSize, paddedSize);

            for (size_t i = 0; i < rowsA; ++i)
                for (size_t j = 0; j < colsA; ++j)
                    paddedA(i, j) = lhs(i, j);
            for (size_t i = 0; i < colsA; ++i)
                for (size_t j = 0; j < colsB; ++j)
                    paddedB(i, j) = rhs(i, j);

            Strassen<T> solver(paddedSize);
            Matrix<T> paddedResult = solver.run(paddedA, paddedB);

            Matrix<T> result(rowsA, colsB);
            for (size_t i = 0; i < rowsA; ++i)
                for (size_t j = 0; j < colsB; ++j)
                    result(i, j) = paddedResult(i, j);
            return result;
        }

    private:
        std::vector<T> _buffer;

        Strassen(size_t n) { _buffer.resize(n * n * 6); }

        template <MatrixLike Lhs, MatrixLike Rhs>
        Matrix<T> run(const Lhs& lhs, const Rhs& rhs)
        {
            size_t n = lhs.Rows();
            Matrix<T> result(n, n);
            multiplyRecursive(result.Slice(0, 0, n, n), lhs, rhs, _buffer.data());
            return result;
        }

        BufferMatrix<T> makeTemp(T* base, size_t index, size_t mid) const
        {
            return BufferMatrix<T>(base + index * mid * mid, mid, mid);
        }

        template <typename Res, MatrixLike M1, MatrixLike M2>
        void multiplyRecursive(Res&& C, const M1& A, const M2& B, T* scratch)
        {
            size_t n = A.Rows();
            if (n <= THRESHOLD)
            {
                C = A * B;
                return;
            }

            size_t mid = n / 2;
            size_t area = mid * mid;

            T* sBase = scratch;
            T* pBase = scratch + 10 * area;
            T* nextScratch = scratch + 17 * area;

            auto A11 = A.Slice(0, 0, mid, mid);
            auto A12 = A.Slice(0, mid, mid, mid);
            auto A21 = A.Slice(mid, 0, mid, mid);
            auto A22 = A.Slice(mid, mid, mid, mid);
            auto B11 = B.Slice(0, 0, mid, mid);
            auto B12 = B.Slice(0, mid, mid, mid);
            auto B21 = B.Slice(mid, 0, mid, mid);
            auto B22 = B.Slice(mid, mid, mid, mid);

            auto S1 = makeTemp(sBase, 0, mid) = B12 - B22;
            auto S2 = makeTemp(sBase, 1, mid) = A11 + A12;
            auto S3 = makeTemp(sBase, 2, mid) = A21 + A22;
            auto S4 = makeTemp(sBase, 3, mid) = B21 - B11;
            auto S5 = makeTemp(sBase, 4, mid) = A11 + A22;
            auto S6 = makeTemp(sBase, 5, mid) = B11 + B22;
            auto S7 = makeTemp(sBase, 6, mid) = A12 - A22;
            auto S8 = makeTemp(sBase, 7, mid) = B21 + B22;
            auto S9 = makeTemp(sBase, 8, mid) = A11 - A21;
            auto S10 = makeTemp(sBase, 9, mid) = B11 + B12;

            auto P1 = makeTemp(pBase, 0, mid);
            auto P2 = makeTemp(pBase, 1, mid);
            auto P3 = makeTemp(pBase, 2, mid);
            auto P4 = makeTemp(pBase, 3, mid);
            auto P5 = makeTemp(pBase, 4, mid);
            auto P6 = makeTemp(pBase, 5, mid);
            auto P7 = makeTemp(pBase, 6, mid);
            multiplyRecursive(P1, A11, S1, nextScratch);
            multiplyRecursive(P2, S2, B22, nextScratch);
            multiplyRecursive(P3, S3, B11, nextScratch);
            multiplyRecursive(P4, A22, S4, nextScratch);
            multiplyRecursive(P5, S5, S6, nextScratch);
            multiplyRecursive(P6, S7, S8, nextScratch);
            multiplyRecursive(P7, S9, S10, nextScratch);

            C.Slice(0, 0, mid, mid) = P5 + P4 - P2 + P6;
            C.Slice(0, mid, mid, mid) = P1 + P2;
            C.Slice(mid, 0, mid, mid) = P2 + P4;
            C.Slice(mid, mid, mid, mid) = P5 + P1 - P3 - P7;
        }
    };
} // namespace Algorithms::Math
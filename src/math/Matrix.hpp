#pragma once

#include <cassert>
#include <concepts>
#include <cstddef>
#include <functional>
#include <type_traits>
#include <utility>
#include <vector>


namespace Algorithms::Math
{
    template <typename T>
    class Matrix;

    template <typename M>
    concept RealMatrix = requires { typename std::remove_cvref_t<M>::is_real_matrix; };

    template <typename M>
    concept MatrixLike = requires(const std::remove_cvref_t<M>& m, size_t i, size_t j) {
        typename std::remove_cvref_t<M>::value_type;
        { m.Rows() } -> std::convertible_to<size_t>;
        { m.Cols() } -> std::convertible_to<size_t>;
        { m(i, j) } -> std::convertible_to<typename std::remove_cvref_t<M>::value_type>;
    };

    template <RealMatrix T>
    class Submatrix
    {
    public:
        using is_real_matrix = std::true_type;
        using value_type = typename std::remove_cvref_t<T>::value_type;
        using reference = value_type&;
        using const_reference = const value_type&;

        Submatrix(T& matrix, size_t rowStart, size_t colStart, size_t rowCount, size_t colCount)
            : _matrix(matrix),
              _rowStart(rowStart),
              _colStart(colStart),
              _rowCount(rowCount),
              _colCount(colCount)
        {
            assert(_rowStart + _rowCount <= _matrix.Rows());
            assert(_colStart + _colCount <= _matrix.Cols());
        }

        template <typename OtherT>
        Submatrix(const Submatrix<OtherT>& other, size_t rowStart, size_t colStart, size_t rowCount,
            size_t colCount)
            : _matrix(other._matrix),
              _rowStart(other._rowStart + rowStart),
              _colStart(other._colStart + colStart),
              _rowCount(rowCount),
              _colCount(colCount)
        {
            assert(rowStart + rowCount <= other.Rows());
            assert(colStart + colCount <= other.Cols());
        }

        template <MatrixLike Other>
        Submatrix& operator=(const Other& other)
        {
            assert(other.Rows() == _rowCount);
            assert(other.Cols() == _colCount);
            for (size_t i = 0; i < _rowCount; ++i)
                for (size_t j = 0; j < _colCount; ++j)
                    (*this)(i, j) = other(i, j);
            return *this;
        }

        size_t Rows() const { return _rowCount; }
        size_t Cols() const { return _colCount; }

        const_reference operator()(size_t i, size_t j) const
        {
            return _matrix(_rowStart + i, _colStart + j);
        }

        reference operator()(size_t i, size_t j)
            requires(!std::is_const_v<T>)
        {
            return _matrix(_rowStart + i, _colStart + j);
        }

        auto Slice(size_t rowStart, size_t colStart, size_t rowCount, size_t colCount)
        {
            assert(rowStart + rowCount <= Rows());
            assert(colStart + colCount <= Cols());
            return Submatrix<T>(*this, rowStart, colStart, rowCount, colCount);
        }

        auto Slice(size_t rowStart, size_t colStart, size_t rowCount, size_t colCount) const
        {
            assert(rowStart + rowCount <= Rows());
            assert(colStart + colCount <= Cols());
            return Submatrix<std::add_const_t<T>>(*this, rowStart, colStart, rowCount, colCount);
        }

    private:
        template <RealMatrix U>
        friend class Submatrix;
        T& _matrix;
        const size_t _rowStart, _colStart, _rowCount, _colCount;
    };

    template <typename T>
    class Matrix
    {
    public:
        using is_real_matrix = std::true_type;
        using value_type = T;
        using reference = value_type&;
        using const_reference = const value_type&;

        Matrix(size_t rows, size_t cols) : _rows(rows), _cols(cols), _data(rows * cols) {}

        Matrix(std::initializer_list<std::initializer_list<T>> init)
        {
            _rows = init.size();
            assert(_rows > 0);
            _cols = init.begin()->size();
            assert(_cols > 0);
            _data.reserve(_rows * _cols);
            for (const auto& row : init)
            {
                assert(row.size() == _cols);
                _data.insert(_data.end(), row.begin(), row.end());
            }
        }

        template <MatrixLike Other>
        Matrix(const Other& other) : _rows(other.Rows()), _cols(other.Cols()), _data(_rows * _cols)
        {
            for (size_t i = 0; i < _rows; ++i)
                for (size_t j = 0; j < _cols; ++j)
                    (*this)(i, j) = other(i, j);
        }

        size_t Rows() const { return _rows; }
        size_t Cols() const { return _cols; }

        reference operator()(size_t i, size_t j)
            requires(!std::is_const_v<T>)
        {
            return _data[i * _cols + j];
        }
        const_reference operator()(size_t i, size_t j) const { return _data[i * _cols + j]; }

        auto Slice(size_t rowStart, size_t colStart, size_t rowCount, size_t colCount)
        {
            assert(rowStart + rowCount <= Rows());
            assert(colStart + colCount <= Cols());
            return Submatrix<Matrix<T>>(*this, rowStart, colStart, rowCount, colCount);
        }

        auto Slice(size_t rowStart, size_t colStart, size_t rowCount, size_t colCount) const
        {
            assert(rowStart + rowCount <= Rows());
            assert(colStart + colCount <= Cols());
            return Submatrix<std::add_const_t<Matrix<T>>>(
                *this, rowStart, colStart, rowCount, colCount);
        }

    private:
        size_t _rows, _cols;
        std::vector<T> _data;
    };

    template <typename T>
    class BufferMatrix
    {
    public:
        using is_real_matrix = std::true_type;
        using value_type = T;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type*;

        BufferMatrix(pointer buffer, size_t rows, size_t cols)
            : _buffer(buffer), _rows(rows), _cols(cols)
        {
        }

        template <MatrixLike Other>
        BufferMatrix& operator=(const Other& other)
        {
            assert(_rows == other.Rows());
            assert(_cols == other.Cols());
            for (size_t i = 0; i < _rows; ++i)
                for (size_t j = 0; j < _cols; ++j)
                    (*this)(i, j) = other(i, j);
            return *this;
        }

        size_t Rows() const { return _rows; }
        size_t Cols() const { return _cols; }

        reference operator()(size_t i, size_t j)
            requires(!std::is_const_v<T>)
        {
            return _buffer[i * _cols + j];
        }
        const_reference operator()(size_t i, size_t j) const { return _buffer[i * _cols + j]; }

        auto Slice(size_t rowStart, size_t colStart, size_t rowCount, size_t colCount)
        {
            assert(rowStart + rowCount <= Rows());
            assert(colStart + colCount <= Cols());
            return Submatrix<BufferMatrix<T>>(*this, rowStart, colStart, rowCount, colCount);
        }

        auto Slice(size_t rowStart, size_t colStart, size_t rowCount, size_t colCount) const
        {
            assert(rowStart + rowCount <= Rows());
            assert(colStart + colCount <= Cols());
            return Submatrix<std::add_const_t<BufferMatrix<T>>>(
                *this, rowStart, colStart, rowCount, colCount);
        }

    private:
        size_t _rows;
        size_t _cols;
        pointer _buffer;
    };

    template <typename T>
    class ScalarWrapper
    {
    public:
        using is_scalar_expression = std::true_type;
        using value_type = T;

        ScalarWrapper(T val) : _val(val) {}

        size_t Rows() const { return 0; }
        size_t Cols() const { return 0; }
        value_type operator()(size_t, size_t) const { return _val; }

    private:
        value_type _val;
    };

    template <typename Lhs, typename Rhs, typename Policy>
    class MatrixExpression
    {
        template <typename T>
        struct Storage
        {
            using type = std::conditional_t<std::is_lvalue_reference_v<T>,
                const std::remove_cvref_t<T>&, std::remove_cvref_t<T>>;
        };

    public:
        using LhsStorage = typename Storage<Lhs>::type;
        using RhsStorage = typename Storage<Rhs>::type;
        using value_type = typename std::remove_cvref_t<Lhs>::value_type;

        MatrixExpression(Lhs&& lhs, Rhs&& rhs)
            : _lhs(std::forward<Lhs>(lhs)), _rhs(std::forward<Rhs>(rhs))
        {
            Policy::ValidateDimensions(_lhs, _rhs);
        }

        size_t Rows() const { return Policy::GetRows(_lhs, _rhs); }
        size_t Cols() const { return Policy::GetCols(_lhs, _rhs); }

        value_type operator()(size_t i, size_t j) const { return Policy::Apply(_lhs, _rhs, i, j); }

        Matrix<value_type> Eval() const { return Matrix<value_type>(*this); }

    private:
        LhsStorage _lhs;
        RhsStorage _rhs;
    };

    template <typename T>
    inline constexpr bool is_scalar_v =
        requires { typename std::remove_cvref_t<T>::is_scalar_expression; };

    template <typename T, typename BinaryOp>
    struct PointwisePolicy
    {
        static void ValidateDimensions(const auto& lhs, const auto& rhs)
        {
            if constexpr (!is_scalar_v<decltype(lhs)> && !is_scalar_v<decltype(rhs)>)
                assert(lhs.Rows() == rhs.Rows() && lhs.Cols() == rhs.Cols());
        }
        static size_t GetRows(const auto& lhs, const auto& rhs)
        {
            return is_scalar_v<decltype(lhs)> ? rhs.Rows() : lhs.Rows();
        }
        static size_t GetCols(const auto& lhs, const auto& rhs)
        {
            return is_scalar_v<decltype(lhs)> ? rhs.Cols() : lhs.Cols();
        }
        static T Apply(const auto& lhs, const auto& rhs, size_t i, size_t j)
        {
            return BinaryOp{}(lhs(i, j), rhs(i, j));
        }
    };

    struct MultiplicationPolicy
    {
        static void ValidateDimensions(const auto& lhs, const auto& rhs)
        {
            assert(lhs.Cols() == rhs.Rows());
        }
        static size_t GetRows(const auto& lhs, const auto& rhs) { return lhs.Rows(); }
        static size_t GetCols(const auto& lhs, const auto& rhs) { return rhs.Cols(); }

        static auto Apply(const auto& lhs, const auto& rhs, size_t i, size_t j)
        {
            using T = typename std::remove_cvref_t<decltype(lhs)>::value_type;
            T sum{};
            size_t k_count = lhs.Cols();
            for (size_t k = 0; k < k_count; ++k)
                sum += lhs(i, k) * rhs(k, j);
            return sum;
        }
    };

    template <MatrixLike Lhs, MatrixLike Rhs>
    auto operator+(Lhs&& lhs, Rhs&& rhs)
    {
        using T = typename std::remove_cvref_t<Lhs>::value_type;
        using Policy = PointwisePolicy<T, std::plus<T>>;
        return MatrixExpression<Lhs&&, Rhs&&, Policy>(
            std::forward<Lhs>(lhs), std::forward<Rhs>(rhs));
    }

    template <MatrixLike Lhs, MatrixLike Rhs>
    auto operator-(Lhs&& lhs, Rhs&& rhs)
    {
        using T = typename std::remove_cvref_t<Lhs>::value_type;
        using Policy = PointwisePolicy<T, std::minus<T>>;
        return MatrixExpression<Lhs&&, Rhs&&, Policy>(
            std::forward<Lhs>(lhs), std::forward<Rhs>(rhs));
    }

    template <MatrixLike Lhs, MatrixLike Rhs>
    auto operator*(Lhs&& lhs, Rhs&& rhs)
    {
        return MatrixExpression<Lhs&&, Rhs&&, MultiplicationPolicy>(
            std::forward<Lhs>(lhs), std::forward<Rhs>(rhs));
    }

    template <MatrixLike Lhs, typename Rhs>
        requires std::convertible_to<std::remove_cvref_t<Rhs>,
            typename std::remove_cvref_t<Lhs>::value_type>
    auto operator*(Lhs&& lhs, Rhs&& rhs)
    {
        using T = typename std::remove_cvref_t<Lhs>::value_type;
        using S = ScalarWrapper<T>;
        using Policy = PointwisePolicy<T, std::multiplies<T>>;

        return MatrixExpression<Lhs&&, S, Policy>(std::forward<Lhs>(lhs), S(static_cast<T>(rhs)));
    }

    template <typename Lhs, MatrixLike Rhs>
        requires std::convertible_to<std::remove_cvref_t<Lhs>,
            typename std::remove_cvref_t<Rhs>::value_type>
    auto operator*(Lhs&& lhs, Rhs&& rhs)
    {
        using T = typename std::remove_cvref_t<Rhs>::value_type;
        using S = ScalarWrapper<T>;
        using Policy = PointwisePolicy<T, std::multiplies<T>>;

        return MatrixExpression<S, Rhs&&, Policy>(S(static_cast<T>(lhs)), std::forward<Rhs>(rhs));
    }
}  // namespace Algorithms::Math
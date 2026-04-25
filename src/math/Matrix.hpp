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
    template <typename M>
    concept MatrixLike = requires(const std::decay_t<M>& m, size_t i, size_t j) {
        typename std::decay_t<M>::value_type;

        { m.rows() } -> std::convertible_to<size_t>;
        { m.cols() } -> std::convertible_to<size_t>;
        { m(i, j) } -> std::convertible_to<typename std::decay_t<M>::value_type>;
    };

    template <typename T>
    class Matrix;

    template <typename M>
    concept RealMatrix =
        std::same_as<std::decay_t<M>, Matrix<typename std::decay_t<M>::value_type>>;

    template <RealMatrix MatrixType>
    class Submatrix
    {
    public:
        using value_type = typename MatrixType::value_type;

        Submatrix(MatrixType& matrix, size_t row_start, size_t col_start, size_t row_count,
            size_t col_count)
            : _matrix(matrix),
              _row_start(row_start),
              _col_start(col_start),
              _row_count(row_count),
              _col_count(col_count)
        {
            assert(_row_start + _row_count <= _matrix.rows());
            assert(_col_start + _col_count <= _matrix.cols());
        }

        template <MatrixLike Other>
        Submatrix& operator=(const Other& other)
        {
            if constexpr (std::same_as<std::decay_t<Other>, Submatrix>)
                if (static_cast<const void*>(this) ==
                    static_cast<const void*>(std::addressof(other)))
                    return *this;

            assert(other.rows() == _row_count);
            assert(other.cols() == _col_count);

            for (size_t i = 0; i < _row_count; ++i)
                for (size_t j = 0; j < _col_count; ++j)
                    _matrix(_row_start + i, _col_start + j) = other(i, j);

            return *this;
        }

        size_t rows() const { return _row_count; }
        size_t cols() const { return _col_count; }

        const value_type& operator()(size_t i, size_t j) const
        {
            assert(i < _row_count && j < _col_count);
            return _matrix(_row_start + i, _col_start + j);
        }

        value_type& operator()(size_t i, size_t j)
        {
            assert(i < _row_count && j < _col_count);
            return _matrix(_row_start + i, _col_start + j);
        }

    private:
        MatrixType& _matrix;
        const size_t _row_start;
        const size_t _col_start;
        const size_t _row_count;
        const size_t _col_count;
    };

    template <typename T>
    class Matrix
    {
    public:
        using value_type = T;

        Matrix(size_t rows, size_t cols) : _rows(rows), _cols(cols), _data(rows * cols)
        {
            assert(_rows > 0);
            assert(_cols > 0);
        }
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
        Matrix(const Other& other)
        {
            _rows = other.rows();
            _cols = other.cols();

            _data.resize(_rows * _cols);

            for (size_t i = 0; i < _rows; ++i)
                for (size_t j = 0; j < _cols; ++j)
                    _data[i * _cols + j] = other(i, j);
        }

        template <MatrixLike Other>
        Matrix& operator=(const Other& other)
        {
            if constexpr (std::same_as<std::decay_t<Other>, Matrix>)
                if (static_cast<const void*>(this) ==
                    static_cast<const void*>(std::addressof(other)))
                    return *this;

            assert(other.rows() > 0);
            assert(other.cols() > 0);

            if (_rows != other.rows() || _cols != other.cols())
            {
                _rows = other.rows();
                _cols = other.cols();
                _data.resize(_rows * _cols);
            }

            for (size_t i = 0; i < _rows; ++i)
                for (size_t j = 0; j < _cols; ++j)
                    _data[i * _cols + j] = other(i, j);

            return *this;
        }

        size_t rows() const { return _rows; }
        size_t cols() const { return _cols; }

        const value_type& operator()(size_t i, size_t j) const
        {
            assert(i < _rows && j < _cols);
            return _data[i * _cols + j];
        }

        value_type& operator()(size_t i, size_t j)
        {
            assert(i < _rows && j < _cols);
            return _data[i * _cols + j];
        }

        Submatrix<Matrix> submatrix(
            size_t row_start, size_t col_start, size_t row_count, size_t col_count)
        {
            return Submatrix<Matrix>(*this, row_start, col_start, row_count, col_count);
        }

        const Submatrix<Matrix> submatrix(
            size_t row_start, size_t col_start, size_t row_count, size_t col_count) const
        {
            return Submatrix<Matrix>(*this, row_start, col_start, row_count, col_count);
        }

    private:
        size_t _rows;
        size_t _cols;
        std::vector<value_type> _data;
    };

    template <typename Op, MatrixLike Lhs, MatrixLike Rhs>
    class MatrixBinaryOp
    {
        template <typename T>
        struct Storage
        {
            using Decayed = std::decay_t<T>;
            using type = std::conditional_t<std::is_lvalue_reference_v<T>, const Decayed&, Decayed>;
        };

    public:
        using value_type = typename std::remove_cvref_t<Lhs>::value_type;

        using LhsStorage = typename Storage<Lhs>::type;
        using RhsStorage = typename Storage<Rhs>::type;

        MatrixBinaryOp(Lhs&& lhs, Rhs&& rhs)
            : _lhs(std::forward<Lhs>(lhs)), _rhs(std::forward<Rhs>(rhs))
        {
            assert(_lhs.rows() == _rhs.rows());
            assert(_lhs.cols() == _rhs.cols());
        }

        size_t rows() const { return _lhs.rows(); }
        size_t cols() const { return _lhs.cols(); }

        value_type operator()(size_t i, size_t j) const
        {
            assert(i < rows() && j < cols());
            return Op{}(_lhs(i, j), _rhs(i, j));
        }

        Matrix<value_type> eval() const { return Matrix<value_type>(*this); }

    private:
        LhsStorage _lhs;
        RhsStorage _rhs;
    };

    template <MatrixLike Lhs, MatrixLike Rhs>
        requires std::same_as<typename std::decay_t<Lhs>::value_type,
            typename std::decay_t<Rhs>::value_type>
    auto operator+(Lhs&& lhs, Rhs&& rhs)
    {
        using T = typename std::remove_cvref_t<Lhs>::value_type;
        return MatrixBinaryOp<std::plus<T>, Lhs&&, Rhs&&>(
            std::forward<Lhs>(lhs), std::forward<Rhs>(rhs));
    }

    template <MatrixLike Lhs, MatrixLike Rhs>
        requires std::same_as<typename std::decay_t<Lhs>::value_type,
            typename std::decay_t<Rhs>::value_type>
    auto operator-(Lhs&& lhs, Rhs&& rhs)
    {
        using T = typename std::remove_cvref_t<Lhs>::value_type;
        return MatrixBinaryOp<std::minus<T>, Lhs&&, Rhs&&>(
            std::forward<Lhs>(lhs), std::forward<Rhs>(rhs));
    }

    template <typename T>
    class ScalarWrapper
    {
    public:
        using value_type = T;
        T value;

        size_t rows() const { return 0; }
        size_t cols() const { return 0; }

        T operator()(size_t, size_t) const { return value; }
    };

    template <MatrixLike Lhs, typename Rhs>
        requires std::same_as<typename std::decay_t<Lhs>::value_type, Rhs>
    auto operator*(Lhs&& lhs, Rhs&& rhs)
    {
        using T = typename std::remove_cvref_t<Lhs>::value_type;
        return MatrixBinaryOp<std::multiplies<T>, Lhs&&, ScalarWrapper<Rhs>&&>(
            std::forward<Lhs>(lhs), ScalarWrapper<Rhs>{rhs});
    }

    template <typename Lhs, MatrixLike Rhs>
        requires std::same_as<Lhs, typename std::decay_t<Rhs>::value_type>
    auto operator*(Lhs&& lhs, Rhs&& rhs)
    {
        return std::forward<Rhs>(rhs) * std::forward<Lhs>(lhs);
    }
}  // namespace Algorithms::Math
// Hello world!


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
    concept RealMatrix = requires { typename std::decay_t<M>::is_real_matrix; };

    template <typename M>
    concept MatrixLike = requires(const std::decay_t<M>& m, size_t i, size_t j) {
        typename std::decay_t<M>::value_type;
        { m.rows() } -> std::convertible_to<size_t>;
        { m.cols() } -> std::convertible_to<size_t>;
        { m(i, j) } -> std::convertible_to<typename std::decay_t<M>::value_type>;
    };

    template <RealMatrix T>
    class Submatrix
    {
    public:
        using is_real_matrix = std::true_type;
        using value_type = typename T::value_type;

        Submatrix(T& matrix, size_t row_start, size_t col_start, size_t row_count, size_t col_count)
            : _matrix(matrix),
              _row_start(row_start),
              _col_start(col_start),
              _row_count(row_count),
              _col_count(col_count)
        {
            assert(_row_start + _row_count <= _matrix.rows());
            assert(_col_start + _col_count <= _matrix.cols());
        }

        template <typename OtherT>
        Submatrix(Submatrix<OtherT>& other, size_t row_start, size_t col_start, size_t row_count,
            size_t col_count)
            : _matrix(other._matrix),
              _row_start(other._row_start + row_start),
              _col_start(other._col_start + col_start),
              _row_count(row_count),
              _col_count(col_count)
        {
            assert(row_start + row_count <= other.rows());
            assert(col_start + col_count <= other.cols());
        }

        template <MatrixLike Other>
        Submatrix& operator=(const Other& other)
        {
            assert(other.rows() == _row_count);
            assert(other.cols() == _col_count);
            for (size_t i = 0; i < _row_count; ++i)
                for (size_t j = 0; j < _col_count; ++j)
                    (*this)(i, j) = other(i, j);
            return *this;
        }

        size_t rows() const { return _row_count; }
        size_t cols() const { return _col_count; }

        const value_type& operator()(size_t i, size_t j) const
        {
            return _matrix(_row_start + i, _col_start + j);
        }

        value_type& operator()(size_t i, size_t j)
            requires(!std::is_const_v<T>)
        {
            return _matrix(_row_start + i, _col_start + j);
        }

        auto submatrix(size_t r_s, size_t c_s, size_t r_c, size_t c_c)
        {
            return Submatrix<T>(*this, r_s, c_s, r_c, c_c);
        }

        auto submatrix(size_t r_s, size_t c_s, size_t r_c, size_t c_c) const
        {
            return Submatrix<std::add_const_t<Matrix<T>>>(*this, r_s, c_s, r_c, c_c);
        }

    private:
        template <RealMatrix U>
        friend class Submatrix;
        T& _matrix;
        const size_t _row_start, _col_start, _row_count, _col_count;
    };

    template <typename T>
    class Matrix
    {
    public:
        using is_real_matrix = std::true_type;
        using value_type = T;

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
        Matrix(const Other& other) : _rows(other.rows()), _cols(other.cols()), _data(_rows * _cols)
        {
            for (size_t i = 0; i < _rows; ++i)
                for (size_t j = 0; j < _cols; ++j)
                    (*this)(i, j) = other(i, j);
        }

        size_t rows() const { return _rows; }
        size_t cols() const { return _cols; }

        value_type& operator()(size_t i, size_t j)
            requires(!std::is_const_v<T>)
        {
            return _data[i * _cols + j];
        }
        const value_type& operator()(size_t i, size_t j) const { return _data[i * _cols + j]; }

        auto submatrix(size_t r_s, size_t c_s, size_t r_c, size_t c_c)
        {
            return Submatrix<Matrix<T>>(*this, r_s, c_s, r_c, c_c);
        }

        auto submatrix(size_t r_s, size_t c_s, size_t r_c, size_t c_c) const
        {
            return Submatrix<std::add_const_t<Matrix<T>>>(*this, r_s, c_s, r_c, c_c);
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

        BufferMatrix(value_type* buffer, size_t rows, size_t cols)
            : _buffer(buffer), _rows(rows), _cols(cols)
        {
        }

        template <MatrixLike Other>
        BufferMatrix& operator=(const Other& other)
        {
            assert(_rows == other.rows());
            assert(_cols == other.cols());
            for (size_t i = 0; i < _rows; ++i)
                for (size_t j = 0; j < _cols; ++j)
                    (*this)(i, j) = other(i, j);
            return *this;
        }

        size_t rows() const { return _rows; }
        size_t cols() const { return _cols; }

        value_type& operator()(size_t i, size_t j)
            requires(!std::is_const_v<T>)
        {
            return _buffer[i * _cols + j];
        }
        const value_type& operator()(size_t i, size_t j) const { return _buffer[i * _cols + j]; }

        auto submatrix(size_t r_s, size_t c_s, size_t r_c, size_t c_c)
        {
            return Submatrix<BufferMatrix<T>>(*this, r_s, c_s, r_c, c_c);
        }

        auto submatrix(size_t r_s, size_t c_s, size_t r_c, size_t c_c) const
        {
            return Submatrix<std::add_const_t<Matrix<T>>>(*this, r_s, c_s, r_c, c_c);
        }

    private:
        size_t _rows;
        size_t _cols;
        value_type* _buffer;
    };

    template <typename T>
    class ScalarWrapper
    {
    public:
        using is_scalar_expression = std::true_type;
        using value_type = T;

        ScalarWrapper(T val) : _val(val) {}

        size_t rows() const { return 0; }
        size_t cols() const { return 0; }
        value_type operator()(size_t, size_t) const { return _val; }

    private:
        value_type _val;
    };

    template <typename T>
    inline constexpr bool is_scalar_v =
        requires { typename std::decay_t<T>::is_scalar_expression; };

    template <typename Op, typename Lhs, typename Rhs>
    class MatrixBinaryOp
    {
        template <typename T>
        struct Storage
        {
            using Decayed = std::decay_t<T>;
            using type = std::conditional_t<std::is_lvalue_reference_v<T>, const Decayed&, Decayed>;
        };

    public:
        using LhsStorage = typename Storage<Lhs>::type;
        using RhsStorage = typename Storage<Rhs>::type;
        using value_type = typename std::decay_t<Lhs>::value_type;

        MatrixBinaryOp(Lhs&& lhs, Rhs&& rhs)
            : _lhs(std::forward<Lhs>(lhs)), _rhs(std::forward<Rhs>(rhs))
        {
            if constexpr (!is_scalar_v<Lhs> && !is_scalar_v<Rhs>)
            {
                assert(_lhs.rows() == _rhs.rows());
                assert(_lhs.cols() == _rhs.cols());
            }
        }

        size_t rows() const
        {
            if constexpr (is_scalar_v<Lhs>)
                return _rhs.rows();
            else
                return _lhs.rows();
        }

        size_t cols() const
        {
            if constexpr (is_scalar_v<Lhs>)
                return _rhs.cols();
            else
                return _lhs.cols();
        }

        value_type operator()(size_t i, size_t j) const { return Op{}(_lhs(i, j), _rhs(i, j)); }

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

    template <MatrixLike Lhs, typename Rhs>
        requires std::convertible_to<std::decay_t<Rhs>, typename std::decay_t<Lhs>::value_type>
    auto operator*(Lhs&& lhs, Rhs&& rhs)
    {
        using T = typename std::decay_t<Lhs>::value_type;
        using S = ScalarWrapper<T>;
        return MatrixBinaryOp<std::multiplies<T>, Lhs&&, S>(
            std::forward<Lhs>(lhs), S(static_cast<T>(rhs)));
    }

    template <typename Lhs, MatrixLike Rhs>
        requires std::convertible_to<std::decay_t<Lhs>, typename std::decay_t<Rhs>::value_type>
    auto operator*(Lhs&& lhs, Rhs&& rhs)
    {
        using T = typename std::decay_t<Rhs>::value_type;
        using S = ScalarWrapper<T>;
        return MatrixBinaryOp<std::multiplies<T>, S, Rhs&&>(
            S(static_cast<T>(lhs)), std::forward<Rhs>(rhs));
    }

    template <MatrixLike Lhs, MatrixLike Rhs>
        requires std::same_as<typename std::decay_t<Lhs>::value_type, typename std::decay_t<Rhs>::value_type>
    auto operator*(Lhs&& lhs, Rhs&& rhs)
    {
        assert(lhs.cols() == rhs.rows());
        using T = typename std::decay_t<Lhs>::value_type;
        Matrix<T> result(lhs.rows(), rhs.cols());
        
        for (size_t i = 0; i < lhs.rows(); ++i)
        {
            for (size_t j = 0; j < rhs.cols(); ++j)
            {
                T sum = 0;
                for (size_t k = 0; k < lhs.cols(); ++k)
                    sum += lhs(i, k) * rhs(k, j);
                result(i, j) = sum;
            }
        }
        return result;
    }
}  // namespace Algorithms::Math
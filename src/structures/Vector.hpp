#pragma once

#include <concepts>
#include <iterator>
#include <memory>


namespace Algorithms::Structures
{
    template <typename T>
    class VectorIterator final
    {
    public:
        using iterator_concept = std::random_access_iterator_tag;
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        VectorIterator() : _ptr(nullptr) {}
        VectorIterator(pointer ptr) : _ptr(ptr) {}
        template <typename U>
        VectorIterator(const VectorIterator<U>& other)
            requires std::convertible_to<U*, T*>
            : _ptr(other.get_ptr())
        {
        }

        reference operator*() const { return *_ptr; }
        pointer operator->() { return _ptr; }
        pointer operator->() const { return _ptr; }

        VectorIterator& operator++()
        {
            ++_ptr;
            return *this;
        }
        VectorIterator operator++(int)
        {
            VectorIterator tmp = *this;
            ++_ptr;
            return tmp;
        }
        VectorIterator& operator--()
        {
            --_ptr;
            return *this;
        }
        VectorIterator operator--(int)
        {
            VectorIterator tmp = *this;
            --_ptr;
            return tmp;
        }

        VectorIterator& operator+=(difference_type n)
        {
            _ptr += n;
            return *this;
        }
        VectorIterator& operator-=(difference_type n)
        {
            _ptr -= n;
            return *this;
        }

        friend VectorIterator operator+(VectorIterator it, difference_type n)
        {
            it += n;
            return it;
        }
        friend VectorIterator operator+(difference_type n, VectorIterator it)
        {
            it += n;
            return it;
        }
        friend VectorIterator operator-(VectorIterator it, difference_type n)
        {
            it -= n;
            return it;
        }
        friend difference_type operator-(const VectorIterator& a, const VectorIterator& b)
        {
            return a._ptr - b._ptr;
        }

        reference operator[](difference_type n) const { return _ptr[n]; }

        bool operator==(const VectorIterator& other) const { return _ptr == other._ptr; }
        bool operator!=(const VectorIterator& other) const { return _ptr != other._ptr; }
        bool operator<(const VectorIterator& other) const { return _ptr < other._ptr; }
        bool operator>(const VectorIterator& other) const { return _ptr > other._ptr; }
        bool operator<=(const VectorIterator& other) const { return _ptr <= other._ptr; }
        bool operator>=(const VectorIterator& other) const { return _ptr >= other._ptr; }

        pointer get_ptr() const { return _ptr; }

    private:
        pointer _ptr;
    };

    template <typename T, typename Allocator = std::allocator<T>>
    class Vector final
    {
    public:
        using value_type = T;
        using allocator_type = Allocator;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = std::allocator_traits<Allocator>::pointer;
        using const_pointer = std::allocator_traits<Allocator>::const_pointer;
        using iterator = VectorIterator<value_type>;
        using const_iterator = VectorIterator<const value_type>;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        Vector() : _allocator(), _data(nullptr), _end(nullptr), _capacity(nullptr) {}
        explicit Vector(size_type count, const T& value)
            : _allocator(), _data(nullptr), _end(nullptr), _capacity(nullptr)
        {
            if (count == 0)
                return;

            reallocate(count);
            try
            {
                for (size_type i = 0; i < count; ++i)
                {
                    std::allocator_traits<Allocator>::construct(_allocator, _data + i, value);
                    _end++;
                }
            }
            catch (...)
            {
                reallocate(0);
                throw;
            }
        }
        explicit Vector(size_type count)
            : _allocator(), _data(nullptr), _end(nullptr), _capacity(nullptr)
        {
            if (count == 0)
                return;

            reallocate(count);
            try
            {
                for (size_type i = 0; i < count; ++i)
                {
                    std::allocator_traits<Allocator>::construct(
                        _allocator, _data + i, value_type());
                    _end++;
                }
            }
            catch (...)
            {
                reallocate(0);
                throw;
            }
        }
        template <class InputIt>
        explicit Vector(InputIt first, InputIt last, const Allocator& alloc = Allocator())
            : _allocator(alloc), _data(nullptr), _end(nullptr), _capacity(nullptr)
        {
            using ValueType = typename std::iterator_traits<InputIt>::value_type;
            static_assert(std::is_constructible_v<T, ValueType>,
                "Input iterator must yield values constructible to T");

            using category = typename std::iterator_traits<InputIt>::iterator_category;
            if constexpr (std::is_base_of_v<std::forward_iterator_tag, category>)
                reallocate(std::distance(first, last));
            while (first != last)
                PushBack(*first++);
        }
        Vector(std::initializer_list<T> init) : Vector(init.begin(), init.end()) {}
        Vector(const Vector& other)
            : _allocator(other._allocator), _data(nullptr), _end(nullptr), _capacity(nullptr)
        {
            if (other.Empty())
                return;

            try
            {
                _data = _allocator.allocate(other.Size());
                _capacity = _data + other.Size();
                _end = _data;
                for (size_type i = 0; i < other.Size(); ++i)
                    PushBack(other._data[i]);
            }
            catch (...)
            {
                reallocate(0);
                throw;
            }
        }
        Vector(Vector&& other) noexcept
            : _allocator(std::move(other._allocator)),
              _data(other._data),
              _end(other._end),
              _capacity(other._capacity)
        {
            other._data = other._end = other._capacity = nullptr;
        }

        ~Vector() { reallocate(0); }
        Vector& operator=(const Vector& other)
        {
            if (this == &other)
                return *this;

            Vector temp(other);
            Swap(temp);
            return *this;
        }
        Vector& operator=(Vector&& other) noexcept
        {
            if (this == &other)
                return *this;

            Swap(other);
            return *this;
        }

        /// Element access
        constexpr reference At(size_type pos)
        {
            if (pos >= Size())
                throw std::out_of_range("Index out of range");
            return _data[pos];
        }
        constexpr const_reference At(size_type pos) const
        {
            if (pos >= Size())
                throw std::out_of_range("Index out of range");
            return _data[pos];
        }

        reference operator[](size_type pos) { return _data[pos]; }
        const_reference operator[](size_type pos) const { return _data[pos]; }

        reference Front() noexcept { return _data[0]; }
        const_reference Front() const noexcept { return _data[0]; }

        reference Back() noexcept { return *(_end - 1); }
        const_reference Back() const noexcept { return *(_end - 1); }

        pointer Data() noexcept { return _data; }
        const_pointer Data() const noexcept { return _data; }

        iterator begin() noexcept { return _data; }
        const_iterator begin() const noexcept { return _data; }
        const_iterator cbegin() const noexcept { return _data; }
        iterator end() noexcept { return _end; }
        const_iterator end() const noexcept { return _end; }
        const_iterator cend() const noexcept { return _end; }
        reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
        reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
        const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
        const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
        const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(cend()); }
        const_reverse_iterator crend() const noexcept { return const_reverse_iterator(cbegin()); }

        /// Capacity
        size_type Size() const noexcept { return _end - _data; }
        bool Empty() const noexcept { return Size() == 0; }
        size_type Capacity() const noexcept { return _capacity - _data; }

        /// Modifiers
        void Clear() noexcept
        {
            while (_end != _data)
            {
                --_end;
                std::allocator_traits<Allocator>::destroy(_allocator, _end);
            }
        }
        void Reserve(size_type newCapacity)
        {
            if (newCapacity > Capacity())
                reallocate(newCapacity);
        }
        void Resize(size_type newSize, const value_type& value = value_type())
        {
            if (newSize < Size())
            {
                while (_end != _data + newSize)
                {
                    --_end;
                    std::allocator_traits<Allocator>::destroy(_allocator, _end);
                }
            }
            else
            {
                if (newSize > Capacity())
                    reallocate(newSize);
                while (_end < _data + newSize)
                {
                    std::allocator_traits<Allocator>::construct(_allocator, _end, value);
                    ++_end;
                }
            }
        }

        void Swap(Vector& other) noexcept
        {
            std::swap(_allocator, other._allocator);
            std::swap(_data, other._data);
            std::swap(_end, other._end);
            std::swap(_capacity, other._capacity);
        }

        void PushBack(const_reference value)
        {
            if (&value >= _data && &value < _end)
            {
                value_type copy = value;
                ensureCapacity();
                std::allocator_traits<Allocator>::construct(_allocator, _end, copy);
            }
            else
            {
                ensureCapacity();
                std::allocator_traits<Allocator>::construct(_allocator, _end, value);
            }
            ++_end;
        }
        void PushBack(value_type&& value)
        {
            if (&value >= _data && &value < _end)
            {
                value_type copy = std::move(value);
                ensureCapacity();
                std::allocator_traits<Allocator>::construct(_allocator, _end, std::move(copy));
            }
            else
            {
                ensureCapacity();
                std::allocator_traits<Allocator>::construct(_allocator, _end, std::move(value));
            }
            ++_end;
        }
        template <typename... Args>
        reference EmplaceBack(Args&&... args)
        {
            if (_end == _capacity)
            {
                value_type temp(std::forward<Args>(args)...);
                ensureCapacity();
                std::allocator_traits<Allocator>::construct(_allocator, _end, std::move(temp));
            }
            else
            {
                std::allocator_traits<Allocator>::construct(
                    _allocator, _end, std::forward<Args>(args)...);
            }
            ++_end;
            return Back();
        }

    private:
        void ensureCapacity()
        {
            if (_capacity - _end == 0)
            {
                if (const auto capacity = Capacity(); capacity == 0)
                    reallocate(1);
                else if (capacity == 1)
                    reallocate(2);
                else
                    reallocate(capacity + capacity / 2);
            }
        }

        /// @brief Перевыделяет память под вектор
        /// @param newCapacity Новый размер вектора
        void reallocate(size_type newCapacity)
        {
            if (newCapacity == 0)
            {
                Clear();
                if (_data)
                    _allocator.deallocate(_data, Capacity());
                _data = _end = _capacity = nullptr;
                return;
            }

            pointer newData = _allocator.allocate(newCapacity);
            size_type currentSize = Size();
            size_type targetSize = std::min(currentSize, newCapacity);
            size_type i = 0;

            try
            {
                for (; i < targetSize; ++i)
                    std::allocator_traits<Allocator>::construct(
                        _allocator, newData + i, std::move_if_noexcept(_data[i]));
            }
            catch (...)
            {
                for (size_type j = 0; j < i; ++j)
                    std::allocator_traits<Allocator>::destroy(_allocator, newData + j);
                _allocator.deallocate(newData, newCapacity);
                throw;
            }

            if (_data)
            {
                for (size_type j = 0; j < currentSize; ++j)
                    std::allocator_traits<Allocator>::destroy(_allocator, _data + j);
                _allocator.deallocate(_data, Capacity());
            }

            _data = newData;
            _end = _data + targetSize;
            _capacity = _data + newCapacity;
        }

        allocator_type _allocator;
        pointer _data, _end, _capacity;
    };

    template <typename T, typename Allocator = std::allocator<T>>
    bool operator==(const Vector<T, Allocator>& lhs, const Vector<T, Allocator>& rhs) noexcept
    {
        const auto n = lhs.Size(); 
        if (n != rhs.Size())
            return false;
        for (size_t i = 0; i < n; ++i)
            if (lhs[i] != rhs[i])
            return false;
        return true;
    }
}
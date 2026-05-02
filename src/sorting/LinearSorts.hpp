#pragma once

#include <array>
#include <concepts>
#include <type_traits>
#include <vector>

#include "InsertionSort.hpp"


namespace Algorithms::Sorting
{
    struct RadixSort;

    struct CountingSort
    {
        template <std::integral T>
        void operator()(std::vector<T>& array, T minValue, T maxValue) const
        {
            if (array.empty())
                return;

            std::vector<T> output(array.size());
            using UT = std::make_unsigned_t<T>;
            size_t range =
                static_cast<size_t>(static_cast<UT>(maxValue) - static_cast<UT>(minValue) + 1);

            auto getIdx = [minValue](T val) { return static_cast<size_t>(val - minValue); };

            std::vector<size_t> countStorage(range, 0);
            countingSortImpl(array, output, countStorage, getIdx);

            std::swap(array, output);
        }

    private:
        friend struct RadixSort;

        template <typename T, typename KeyExtractor, typename Counter>
        static void countingSortImpl(
            const std::vector<T>& src, std::vector<T>& dst, Counter&& count, KeyExtractor&& getIdx)
        {
            if (src.empty())
                return;

            for (const auto& value : src)
                count[getIdx(value)]++;

            for (size_t i = 1; i < count.size(); ++i)
                count[i] += count[i - 1];

            for (size_t i = src.size(); i > 0; --i)
            {
                size_t idx = getIdx(src[i - 1]);
                dst[count[idx] - 1] = src[i - 1];
                count[idx]--;
            }
        }
    };

    struct RadixSort
    {
        template <std::integral T>
        void operator()(std::vector<T>& array) const
        {
            if (array.empty())
                return;

            using UT = std::make_unsigned_t<T>;
            std::vector<T> buffer(array.size());
            auto* src = &array;
            auto* dst = &buffer;

            const int bytesInType = sizeof(T);
            for (int byteIdx = 0; byteIdx < bytesInType; ++byteIdx)
            {
                int shift = byteIdx * 8;
                auto getIdx = [byteIdx, shift, bytesInType](T value)
                {
                    UT uValue = static_cast<UT>(value);
                    if constexpr (std::is_signed_v<T>)
                        if (byteIdx == bytesInType - 1)
                            uValue ^= (static_cast<UT>(1) << (sizeof(T) * 8 - 1));
                    return static_cast<size_t>((uValue >> shift) & 0xFF);
                };

                std::array<size_t, 256> count{};
                CountingSort::countingSortImpl(*src, *dst, count, getIdx);
                std::swap(src, dst);
            }

            if (src != &array)
                array = std::move(buffer);
        }
    };

    struct BucketSort
    {
        template <std::floating_point T>
        void operator()(std::vector<T>& array) const
        {
            if (array.size() < 2)
                return;

            auto [minIt, maxIt] = std::minmax_element(array.begin(), array.end());
            T minValue = *minIt;
            T maxValue = *maxIt;

            if (minValue == maxValue)
                return;

            const size_t n = array.size();
            std::vector<std::vector<T>> buckets(n);
            for (const auto& value : array)
            {
                const T normalized = (value - minValue) / (maxValue - minValue);
                const size_t index = static_cast<size_t>(normalized * (n - 1));
                buckets[index].push_back(value);
            }

            InsertionSort insertionSort;
            size_t arrayIdx = 0;
            for (auto& bucket : buckets)
            {
                if (bucket.empty())
                    continue;

                insertionSort(bucket);
                for (const auto& val : bucket)
                    array[arrayIdx++] = val;
            }
        }
    };
} // namespace Algorithms::Sorting
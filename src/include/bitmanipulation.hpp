#pragma once

#include <climits>
#include <cstdint>

namespace bitmanipulation {

/**
 * Creates a bitmask. E.g. mask(2,2) = 0b1100
 * @param bits  the number of set bits in the mask
 * @param shift the set bits in the mask will be shifted to the left by this amount
 */
[[nodiscard]] constexpr auto mask(const unsigned bits, const unsigned shift = 0) -> uintmax_t
{
    return ~(static_cast<uintmax_t>(~0) << bits) << shift;
}

/**
 * Sets bits in a given value and returns the value with the additional set bits.
 * E.g. set_bits(0b1100, 2, 0) = 0b1111
 * @param value the given value
 * @param bits  the number of bits to set
 * @param shift the additionally set bits will be shifted to the left by this amount
 */
template <class T>
[[nodiscard]] constexpr auto set_bits(const T value, const unsigned bits, const unsigned shift = 0) -> T
{
    const T mask { static_cast<T>(bitmanipulation::mask(bits, shift)) };
    return value | mask;
}

/**
 * Clears bits in a given value and returns the value with the cleared bits.
 * E.g. clear_bits(0b1111, 2, 1) = 0b1001
 * @param value the given value
 * @param bits  the number of bits to clear
 * @param shift the cleared bits will be shifted to the left by this amount
 */
template <class T>
[[nodiscard]] constexpr auto clear_bits(const T value, const unsigned bits, const unsigned shift = 0) -> T
{
    const T mask { static_cast<T>(bitmanipulation::mask(bits, shift)) };
    return value & static_cast<T>(~mask);
}

/**
 * Returns the number of set bits in the given value.
 * E.g. count_bits_set(0b11) = 2
 * @param value the given value
 */
template <class T>
[[nodiscard]] constexpr auto count_bits_set(T value) -> unsigned
{
    unsigned count { 0U };
    for (; value; count++) {
        value = value & static_cast<T>(value - 1);
    }
    return count;
}

template <class T>
[[nodiscard]] constexpr auto popcnt(T value) -> unsigned { return count_bits_set(value); }

/**
 * Returns the number of leading zeroes in the given value.
 * E.g. leading_zeroes_count(0b00001111) = 4
 * @param value the given value
 */
template <class T>
[[nodiscard]] constexpr auto leading_zeroes_count(const T value) -> unsigned
{
    if (value == 0) {
        return sizeof(value) * CHAR_BIT;
    }

    unsigned       count {                       0U };
    const unsigned len   { sizeof(value) * CHAR_BIT };

    for (unsigned i = 1; i <= len; i++) {
        if (bitmanipulation::mask(1, len - i) & value) {
            break;
        }
        count++;
    }

    return count;
}

template <class T>
[[nodiscard]] constexpr auto lzcnt(const T value) -> unsigned { return leading_zeroes_count(value); }

/**
 * Returns the number of trailing zeroes in the given value.
 * E.g. trailing_zeroes_count(0b1100) = 2
 * @param value the given value
 */
template <class T>
constexpr auto trailing_zeroes_count(const T value) -> unsigned
{
    if (value == 0) {
        return sizeof(value) * CHAR_BIT;
    }

    unsigned       count {                       0U };
    const unsigned len   { sizeof(value) * CHAR_BIT };

    for (unsigned i = 0; i < len; i++) {
        if (bitmanipulation::mask(1, i) & value) {
            break;
        }
        count++;
    }

    return count;
}

template <class T>
[[nodiscard]] constexpr auto tzcnt(const T value) -> unsigned { return trailing_zeroes_count(value); }

/**
 * Isolates the lowest clear bit in the given value.
 * E.g. isolate_lowest_clear_bit(0b11100011) = 0b11111011
 * @param value the given value
 */
template <class T>
[[nodiscard]] constexpr auto isolate_lowest_clear_bit(const T value) -> T
{
    return value | static_cast<T>(~(value + 1));
}

template <class T>
[[nodiscard]] constexpr auto blci(const T value) -> T { return isolate_lowest_clear_bit(value); }

/**
 * Isolates the lowest set bit in the given value.
 * E.g. isolate_lowest_set_bit(0b11100011) = 0b00000001
 * @param value the given value
 */
template <class T>
[[nodiscard]] constexpr auto isolate_lowest_set_bit(const T value) -> T
{
    return value & static_cast<T>(-value);
}

template <class T>
[[nodiscard]] constexpr auto blsi(const T value) -> T { return isolate_lowest_set_bit(value); }

/**
 * Clears all set bits to the right of the first clear bit in the given value.
 * E.g. fill_from_lowest_clear_bit(0b11101011) = 0b11101000
 * @param value the given value
 */
template <class T>
[[nodiscard]] constexpr auto fill_from_lowest_clear_bit(const T value) -> T
{
    if (bitmanipulation::popcnt(value) == sizeof(value) * CHAR_BIT) {
        return value;
    }
    return value & static_cast<T>(value + 1);
}

template <class T>
[[nodiscard]] constexpr auto blcfill(const T value) -> T { return fill_from_lowest_clear_bit(value); }

/**
 * Sets all clear bits to the right of the first set bit in the given value.
 * E.g. fill_from_lowest_set_bit(0b01110100) = 0b01110111
 * @param value the given value
 */
template <class T>
[[nodiscard]] constexpr auto fill_from_lowest_set_bit(const T value) -> T
{
    if (bitmanipulation::popcnt(value) == 0) {
        return 0;
    }
    return value | static_cast<T>(value - 1);
}

template <class T>
[[nodiscard]] constexpr auto blsfill(const T value) -> T { return fill_from_lowest_set_bit(value); }

/**
 * Clears the lowest set bit in the given value.
 * E.g. clear_lowest_set_bit(0b11100010) = 0b11100000
 * @param value the given value
 */
template <class T>
[[nodiscard]] constexpr auto clear_lowest_set_bit(const T value) -> T
{
    return value & static_cast<T>(value - 1);
}

template <class T>
[[nodiscard]] constexpr auto blsc(const T value) -> T { return clear_lowest_set_bit(value); }

/**
 * Sets the lowest clear bit in the given value.
 * E.g. set_lowest_clear_bit(0b11100011) = 0b11100111
 * @param value the given value
 */
template <class T>
[[nodiscard]] constexpr auto set_lowest_clear_bit(const T value) -> T
{
    return value | static_cast<T>(value + 1);
}

template <class T>
[[nodiscard]] constexpr auto blcs(const T value) -> T { return set_lowest_clear_bit(value); }

} // namespace bitmanipulation

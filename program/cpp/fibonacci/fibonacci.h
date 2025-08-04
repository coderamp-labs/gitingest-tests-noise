/**
 * @file fibonacci.h
 * @author Ahmed Al-Mansouri (ahmed@bridgesforpeace.org)
 * @brief Fibonacci implementation in C++
 * @date 2025-08-04
 *
 * @copyright Copyright Bridges for Peace (c) 2025
 */

#pragma once

#include <cstdint>
#include <array>
#include <vector>

namespace Fibonacci {

    /**
     * @brief Calculates the nth Fibonacci number using constexpr
     * 
     * This function uses compile-time evaluation for small values of n.
     * For larger values, it falls back to runtime calculation.
     * 
     * @param n The position in the Fibonacci sequence (0-based)
     * @return The nth Fibonacci number
     */
    constexpr uint64_t fibonacci(uint32_t n) {
        if (n <= 1) return n;
        return fibonacci(n - 1) + fibonacci(n - 2);
    }

    /**
     * @brief Calculates Fibonacci numbers up to n using constexpr
     * 
     * Creates an array of Fibonacci numbers from F(0) to F(n).
     * 
     * @param n The maximum position in the Fibonacci sequence
     * @return Array containing Fibonacci numbers
     */
    template<size_t N>
    constexpr auto fibonacci_sequence() {
        std::array<uint64_t, N + 1> result{};
        for (size_t i = 0; i <= N; ++i) {
            result[i] = fibonacci(i);
        }
        return result;
    }

    /**
     * @brief Checks if a number is a Fibonacci number using constexpr
     * 
     * @param num The number to check
     * @return true if the number is a Fibonacci number, false otherwise
     */
    constexpr bool is_fibonacci(uint64_t num) {
        if (num <= 1) return true;
        
        uint64_t a = 0, b = 1;
        while (b < num) {
            uint64_t temp = a + b;
            a = b;
            b = temp;
        }
        return b == num;
    }

    /**
     * @brief Gets the position of a Fibonacci number in the sequence
     * 
     * @param num The Fibonacci number
     * @return The position (0-based), or -1 if not a Fibonacci number
     */
    constexpr int fibonacci_position(uint64_t num) {
        if (num <= 1) return static_cast<int>(num);
        
        uint64_t a = 0, b = 1;
        int position = 1;
        
        while (b < num) {
            uint64_t temp = a + b;
            a = b;
            b = temp;
            ++position;
        }
        
        return (b == num) ? position : -1;
    }

    // Pre-computed Fibonacci numbers for common use cases
    constexpr uint64_t FIBONACCI_20[] = {
        fibonacci(0), fibonacci(1), fibonacci(2), fibonacci(3), fibonacci(4),
        fibonacci(5), fibonacci(6), fibonacci(7), fibonacci(8), fibonacci(9),
        fibonacci(10), fibonacci(11), fibonacci(12), fibonacci(13), fibonacci(14),
        fibonacci(15), fibonacci(16), fibonacci(17), fibonacci(18), fibonacci(19), fibonacci(20)
    };

} // namespace Fibonacci 
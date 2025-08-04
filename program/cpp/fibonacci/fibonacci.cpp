#include "fibonacci.h"
#include <iostream>
#include <iomanip>

using namespace Fibonacci;

int main() {
    std::cout << "🔢 Constexpr Fibonacci Implementation\n";
    std::cout << "=====================================\n\n";

    // Demonstrate compile-time Fibonacci calculation
    std::cout << "📊 First 20 Fibonacci numbers (compile-time):\n";
    for (int i = 0; i <= 20; ++i) {
        auto fib = fibonacci(i);
        std::cout << "F(" << std::setw(2) << i << ") = " << std::setw(8) << fib << "\n";
    }

    std::cout << "\n🎯 Using pre-computed array:\n";
    for (int i = 0; i <= 20; ++i) {
        std::cout << "F(" << std::setw(2) << i << ") = " << std::setw(8) << FIBONACCI_20[i] << "\n";
    }

    // Demonstrate Fibonacci sequence template
    std::cout << "\n📋 Fibonacci sequence using template (first 10):\n";
    auto seq_10 = fibonacci_sequence<10>();
    for (size_t i = 0; i <= 10; ++i) {
        std::cout << "F(" << std::setw(2) << i << ") = " << std::setw(4) << seq_10[i] << "\n";
    }

    // Demonstrate Fibonacci number checking
    std::cout << "\n🔍 Checking if numbers are Fibonacci:\n";
    uint64_t test_numbers[] = {0, 1, 2, 3, 4, 5, 8, 13, 21, 34, 55, 89, 100, 144, 233};
    
    for (auto num : test_numbers) {
        bool is_fib = is_fibonacci(num);
        std::cout << num << " is " << (is_fib ? "✅" : "❌") << " a Fibonacci number";
        
        if (is_fib) {
            int pos = fibonacci_position(num);
            std::cout << " (position " << pos << ")";
        }
        std::cout << "\n";
    }

    // Demonstrate runtime vs compile-time
    std::cout << "\n⚡ Runtime vs Compile-time comparison:\n";
    
    // Compile-time calculation
    constexpr auto compile_time_fib = fibonacci(15);
    std::cout << "Compile-time F(15) = " << compile_time_fib << "\n";
    
    // Runtime calculation
    uint32_t n = 15;
    auto runtime_fib = fibonacci(n);
    std::cout << "Runtime F(15) = " << runtime_fib << "\n";
    
    std::cout << "Results match: " << (compile_time_fib == runtime_fib ? "✅" : "❌") << "\n";

    // Performance demonstration
    std::cout << "\n🚀 Performance demonstration:\n";
    std::cout << "Calculating F(40) using constexpr...\n";
    
    // This will be calculated at compile-time if possible
    auto fib_40 = fibonacci(40);
    std::cout << "F(40) = " << fib_40 << "\n";

    std::cout << "\n✨ Constexpr Fibonacci implementation complete!\n";
    std::cout << "Key features demonstrated:\n";
    std::cout << "• Compile-time calculation for small values\n";
    std::cout << "• Template-based sequence generation\n";
    std::cout << "• Fibonacci number validation\n";
    std::cout << "• Position finding in sequence\n";
    std::cout << "• Pre-computed arrays for common values\n";

    return 0;
} 
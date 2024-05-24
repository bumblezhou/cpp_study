#include <iostream>
#include <bitset>
#include <memory>

using namespace std;

template<typename T>
constexpr T pi = T(3.1415926535897932385);

template<typename T>
constexpr T area(T radius) {
    return pi<T> * radius * radius;
}

constexpr int fibonacci(int n) {
    return (n <= 1) ? n : fibonacci(n - 1) + fibonacci(n - 2);
}

template<typename T>
void print_binary(T value) {
    std::bitset<sizeof(T) * 8> binary(value);
    std::cout << "value:" << value << ", 0b" << binary << std::endl;
}

struct Point {
    int x;
    int y;
};

int main() {
    // 1. Generic lambdas:
    auto add = [](auto x, auto y) { return x + y; };
    std::cout << "Lambda add(5, 3): " << add(5, 3) << std::endl; // Outputs: 8
    std::cout << "Lambda add(3.5, 2.5): " << add(3.5, 2.5) << std::endl; // Outputs: 6.0

    // 2. Variable templates:
    double radius1 = 5.0;
    double a1 = area(radius1);
    std::cout << "area(5.0): " << a1 << std::endl;

    float radius2 = 3.25;
    float a2 = area(radius2);
    std::cout << "area(3.25): " << a2 << std::endl;

    // 3. Relaxed constexpr restrictions:
    constexpr int result = fibonacci(10);
    std::cout << "fibonacci(10):" << result << std::endl; // Outputs: 55

    // 4. Binary literals and digit separators:
    int binary_value = 0b1111'1111'1111'1111'1010'1010'1100'1100;
    int big_number = 1'000'000;
    print_binary(binary_value);
    std::cout << "big_number:" << big_number << std::endl; // Outputs: 1000000

    // 5. std::make_unique:
    unique_ptr<int> ptr1 = make_unique<int>(42);
    cout << "ptr1:" << *ptr1 << endl;
    *ptr1 = 25;
    cout << "ptr1:" << *ptr1 << endl;

    return 0;
}
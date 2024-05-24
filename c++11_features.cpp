#include <iostream>
#include <typeinfo>
#include <vector>
#include <memory>
#include <string>
using namespace std;

// Custom implementation of make_unique for C++11
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

struct Point
{
    int x;
    int y;
};

enum class Color {
    Red,
    Green,
    Blue
};

constexpr int square(int x) { return x * x; };

// Function taking an lvalue reference
void lvalue_reference(int& x) {
    std::cout << "Received lvalue reference: " << std::dec << x << ", addr(x): 0x" << std::hex << reinterpret_cast<uintptr_t>(&x) << std::endl;
}

// Function taking an rvalue reference
void rvalue_reference(int&& x) {
    std::cout << "Received rvalue reference: " << std::dec << x << ", addr(x): 0x" << std::hex << reinterpret_cast<uintptr_t>(&x) << std::endl;
}

// Function taking a const lvalue reference
void const_lvalue_reference(const int& x) {
    std::cout << "Received const lvalue reference: " << std::dec << x << ", addr(x): 0x" << std::hex << reinterpret_cast<uintptr_t>(&x) << std::endl;
}

// Base case for the recursion (when there are no more arguments)
void print() {
    std::cout << std::endl;
}

// Variadic template function to print any number of arguments
template<typename T, typename... Args>
void print(T&& first, Args&&... args) {
    std::cout << std::forward<T>(first) << " ";
    print(std::forward<Args>(args)...); // Recursively call print with the remaining arguments
}

int main() {
    // 1. auto keyword:
    auto value = 10;
    auto text = "hello";
    auto num = 0.25;

    cout << "Type of value: " << typeid(value).name() << ", Value: " << value << endl;
    cout << "Type of text: " << typeid(text).name() << ", Value: " << text << endl;
    cout << "Type of num: " << typeid(num).name() << ", Value: " << num << endl;

    // 2. Range-based for loops:
    vector<int> numbers = {1, 2, 3, 4, 5};
    for (auto& num : numbers) {
        cout << "Num: " << num << endl;
    }

    // 3. Lambda expressions:
    auto add = [](int a, int b) { return a + b; };
    cout << "Lambda add(3, 5): " << add(3, 5) << endl;

    // 4. nullptr:
    int* ptr = nullptr;
    if (ptr == nullptr) {
        cout << "ptr is null" << endl;
    }

    // 5. Smart pointers (std::unique_ptr, std::shared_ptr):
    unique_ptr<int> ptr1 = make_unique<int>(42);
    cout << "ptr1:" << *ptr1 << endl;
    *ptr1 = 25;
    cout << "ptr1:" << *ptr1 << endl;

    shared_ptr<int> ptr2 = std::make_shared<int>(51);
    cout << "ptr2:" << *ptr2 << endl;
    shared_ptr<int> ptr3 = ptr2;
    cout << "ptr2:" << *ptr2 << endl;
    cout << "ptr3:" << *ptr3 << endl;
    *ptr3 = 25;
    cout << "ptr2:" << *ptr2 << endl;
    cout << "ptr3:" << *ptr3 << endl;

    // 6. Move semantics (std::move):
    vector<int> test_list = {1, 2, 3, 4, 5};
    cout << "items in test_list:" << endl;
    for (auto& item : test_list) {
        cout << "item: " << item << endl;
    }
    vector<int> another_list = std::move(test_list);
    cout << "items in another_list:" << endl;
    for (auto& item : another_list) {
        cout << "item: " << item << endl;
    }
    if (test_list.empty()) {
        cout << "test_list is empty now." << endl;
    }

    string str1 = "Hello";
    string str2 = std::move(str1);
    cout << "str1:" << str1 << ", str2:" << str2 << endl;
    if (str1.empty()) {
        cout << "str1 is empty now." << endl;
    }

    // 7. Initializer lists:
    vector<Point> points = { {0, 0}, {100, 100} };
    for(auto& point : points) {
        cout << "point(x:" << point.x << ", y:" << point.y << ")" << endl;
    }

    // 8. constexpr:
    constexpr int result = square(25);
    cout << "result of square(25):" << result << endl;

    // 9. Rvalue references:
    int a = 42;

    // Ordinary reference
    int& ref = a;
    std::cout << "Address of a: 0x" << std::hex << &a << ", Value of a:" << std::dec << a << std::endl;
    std::cout << "Address of ref: 0x" << std::hex << ref << ", Value of ref:" << std::dec << ref << std::endl;
    lvalue_reference(ref);  // Passed by lvalue reference

    // Rvalue reference
    rvalue_reference(100);  // Passed by rvalue reference
    rvalue_reference(std::move(a));  // Passed by rvalue reference after std::move
    
    // Const lvalue reference
    const_lvalue_reference(a);  // Passed by const lvalue reference

    int&& b = 37;   // rvalue reference to temporary
    std::cout << "Address of b: 0x" << std::hex << &b << ", Value of b:" << std::dec << b << std::endl;

    // 10. Strongly-typed enums:
    // Declaration and initialization
    Color myColor = Color::Red;
    // Comparison
    if (myColor == Color::Red) {
        std::cout << "The color is Red." << std::endl;
    }
    // Assigning enum value
    myColor = Color::Green;
    // Switch statement
    switch (myColor) {
        case Color::Red:
            std::cout << "The color is Red." << std::endl;
            break;
        case Color::Green:
            std::cout << "The color is Green." << std::endl;
            break;
        case Color::Blue:
            std::cout << "The color is Blue." << std::endl;
            break;
    }
    
    // 11. Static assertions (static_assert):
    const Color test_color = Color::Red;
    static_assert(sizeof(int) == 4, "int must be 4 bytes");
    static_assert(test_color == Color::Red, "myColor is not Blue");

    // 12. Variadic templates:
    print("hello", 1, 2, 3, " ", "world:", 3.1514926);

    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

// Define a printable concept
template<typename T>
concept Printable = requires(T x) {
    { std::cout << x }; // Expression to check if std::cout supports the << operator with type T
};

// Function template constrained by the printable concept
template<Printable T>
void print(const T& value) {
    std::cout << value << std::endl;
}

// Another concetp for a sortable container
template<typename Container>
concept SortableContainer = requires(Container container) {
    std::begin(container);
    std::end(container);
    std::sort(std::begin(container), std::end(container));
};

// Function template constrained by the SortableContainer concept
template<SortableContainer T>
void sort_and_print(T& container) {
    std::sort(std::begin(container), std::end(container));
    for(const auto& elem : container) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

int main() {
    // 1. Concepts
    // Example usage withe different types, Only accept printable parameters
    print(10);
    print("Hello, Concepts!");

    std::vector<int> numbers = {3, 4, 6, 1, 2, 0, 4, 5, 7, 9, 8, 1, 3};
    sort_and_print(numbers);  // Only accept sortable parameters

    // // 2. Ranges
    // // 2.1 Range Adaptor
    // auto result = numbers | std::views::filter([](int x) { return x % 2 == 0; })
    //                       | std::views::transform([](int x) { return x * x; });
    // for (auto& n : numbers) {
    //     std::cout << n << " ";
    // }
    // std::cout << std::endl;

    // // 2.2 Comon Range Types
    // auto subrange = std::ranges::subrange(numbers.begin() + 1, numbers.end() - 1);
    // for (auto& n : numbers) {
    //     std::cout << n << " ";
    // }
    // std::cout << std::endl;
    
    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <coroutine>
#include <functional>
#include <thread>

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

struct Awaiter {
    bool await_ready() {
        cout << "[Awaiter] await_ready" << endl;
        return false;
    }

    void await_suspend(std::coroutine_handle<> handle) {
        cout << "[Awaiter] await_suspend" << endl;
    }

    void await_resume() {
        cout << "[Awaiter] await_resume" << endl;
    }
};

// Promese
struct Co {
    struct promise_type
    {
        auto get_return_object() {
            return Co{ std::coroutine_handle<promise_type>::from_promise(*this) };
        }

        auto initial_suspend() {
            cout << "[promise_type] initial_suspend" << endl;
            return std::suspend_always{};
        }

        auto final_suspend() noexcept {
            cout << "[promise_type] final_suspend" << endl;
            return std::suspend_always{};
        }
        void unhandled_exception() { std::terminate(); }
        void return_void() {
            cout << "[promise_type] return_void" << endl;
        }
        int m_value = -1;
        std::suspend_always yield_value(int value) {
            m_value = value;
            return {};
        }
    };
    std::coroutine_handle<promise_type> handle;
};

// coroutine
Co run() {
    cout << "[run] before" << endl;
    // co_await Awaiter {};
    co_yield 1;
    co_yield 2;
    co_yield 3;
    cout << "[run] after" << endl;
}

int main() {
    // 1. Concepts
    // Example usage withe different types, Only accept printable parameters
    print(10);
    print("Hello, Concepts!");

    std::vector<int> numbers = {3, 4, 6, 1, 2, 0, 4, 5, 7, 9, 8, 1, 3};
    sort_and_print(numbers);  // Only accept sortable parameters

    // 2. Ranges
    // 2.1 Range Adaptor
    auto filter_and_squares = numbers | std::views::filter([](int x) { return x % 2 == 0; }) | std::views::transform([](int x) { return x * x; });
    for (auto n : filter_and_squares) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    // 2.2 Common Range Types
    auto subrange = std::ranges::subrange(numbers.begin() + 1, numbers.end() - 1);
    for (auto& n : subrange) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    subrange = numbers | std::views::take(5);
    for (auto& n : subrange) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    // 2.3 Range Algorithms
    // Calculate the sum of all elements in the range
    auto sum = std::accumulate(numbers.begin(), numbers.end(), 0);
    std::cout << "Sum of numbers: " << sum << std::endl;

    // 3. Coroutines
    auto co = run();
    for(int i = 0; !co.handle.done(); ++i) {
        // cout << "[main] resume " << i << endl;
        cout << "[main] resume " << i << "=>" << co.handle.promise().m_value << endl;
        co.handle.resume();
    }
    
    return 0;
}

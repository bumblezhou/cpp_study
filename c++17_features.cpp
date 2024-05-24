#include <iostream>
#include <tuple>
#include <optional>
#include <variant>
#include <type_traits>
#include <string_view>
#include "header.hpp"
#include <filesystem>
#include <fstream>
using namespace std;
namespace fs = filesystem;

struct Point {
    int x;
    int y;
};

optional<int> get_optional_value(bool has_value) {
    if(has_value) {
        return 42;
    } else {
        return nullopt; // Represents no value
    }
}

struct PrintVisitor {
    void operator()(int value) const {
        cout << "var Value is an int: " << value << endl;
    }

    void operator()(double value) const {
        cout << "var Value is a double: " << value << endl;
    }

    void operator()(const string& value) const {
        cout << "var Value is a string: " << value << endl;
    }
};

template<typename T>
void print_size(T value) {
    if constexpr (is_integral<T>::value) {
        cout << "Size of " << value << " is " << sizeof(T) << " bytes." << endl;
    } else if constexpr (is_floating_point<T>::value) {
        cout << "Size of " << value << " is " << sizeof(T) << " bytes." << endl;
    } else {
        cout << "Cannot determine size of the unknown type." << endl;
    }
}

template<typename... Args>
auto sum(Args... args) {    // the fold expression (args + ...), known as a "binary fold", expands to (1 + 2 + 3 + 4 + 5) when sum(1, 2, 3, 4, 5) is called.
    return (args + ...);
}

template<typename... Args>
void print(Args... args) {
    (cout << ... << args) << endl;
}

[[nodiscard]] int get_no_discard_value() {
    return 42;
}

int main() {
    // 1. Structured bindings
    tuple<int, double, string> my_tuple(42, 3.14, "hello");
    auto [a, b, c] = my_tuple; // Structured binding
    cout << "a: " << a << ", b: " << b << ", c: " << c << endl;

    Point p {10, 20};
    auto [x, y] = p;
    cout << "x: " << x << ", y: " << y << endl;

    // 2. if with initializer:
    int m = 10, n = 20;
    if (int sum = m + n; sum > 0) {
        cout << "sum is positive: " << sum << endl;
    } else {
        cout << "sum is non-positive: " << sum << endl;
    }

    // 3. optional:
    optional<int> opt; // Default-initialized to empty
    if (opt.has_value()) {
        cout << "Value is: " << opt.value() << endl;
    } else {
        cout << "No value present" << endl;
    }
    opt = 42;
    if (opt.has_value()) {
        cout << "Value is: " << opt.value() << endl;
    } else {
        cout << "No value present" << endl;
    }

    opt = get_optional_value(false);
    if (opt.has_value()) {
        cout << "Value is: " << opt.value() << endl;
    } else {
        cout << "No value present" << endl;
    }
    opt = get_optional_value(true);
    if (opt.has_value()) {
        cout << "Value is: " << opt.value() << endl;
    } else {
        cout << "No value present" << endl;
    }

    // 4. variant:
    variant<int, double, string> var;

    var = 42; // Assign int
    cout << "var Value is: " << get<int>(var) << endl;

    var = 3.14; // Assign double
    cout << "var Value is: " << get<double>(var) << endl;

    var = "hello"; // Assign string
    cout << "var Value is: " << get<string>(var) << endl;

    variant<int, double, string> var1 = 3.14;

    if (holds_alternative<int>(var1)) {
        cout << "var Value is an int: " << get<int>(var1) << endl;
    } else if (holds_alternative<double>(var1)) {
        cout << "var Value is a double: " << get<double>(var1) << endl;
    } else if (holds_alternative<string>(var1)) {
        cout << "var Value is a string: " << get<string>(var1) << endl;
    }

    variant<int, double, string> var3 = "hello";

    visit(PrintVisitor{}, var3);

    // 4. constexpr if:
    print_size(42);   // Prints the size of int
    print_size(3.14); // Prints a message for float types
    print_size("hello"); // Prints a message for string types
    print_size(p); // Prints a message for custom type(Point)

    // 5. string_view
    string_view sv = "Hello, World!";
    cout << "Length: " << sv.length() << endl;
    cout << "First character: " << sv[0] << endl;
    cout << "Last character: " << sv.back() << endl;
    cout << "Substring: " << sv.substr(7, 5) << endl;


    // 6. Fold expressions
    cout << "Sum: " << sum(1, 2, 3, 4, 5) << endl; // Output: 15
    print("Hello", ", ", "world!"); // Output: Hello, world!

    // 7. Inline variables:
    cout << "Value from c++17_features.cpp: " << inline_value << endl;

    // 8. Filesystem library:
    fs::path path = "./static/test.html";
    if (fs::exists(path)) {
        cout << "Path exists" << endl;
    } else {
        cout << "Path does not exist" << endl;
    }
    if (fs::is_regular_file(path)) {
        cout << "Path is a regular file" << endl;
    } else {
        cout << "Path is not a regular file" << endl;
    }
    if (fs::is_directory(path)) {
        cout << "Path is a directory" << endl;
    } else {
        cout << "Path is not a directory" << endl;
    }

    fs::path directory = "./static/";
    for (const auto& entry : fs::directory_iterator(directory)) {
        cout << entry.path() << endl;
    }

    fs::path test_directory = "./test_directory/";
    fs::create_directory(test_directory);
    cout << "create directory: " << test_directory << endl;
    string filename = "empty_file.txt";
    fs::path file_path = test_directory / filename;
    ofstream file(file_path);
    if(file.is_open()) {
        cout << "Empty file created successfully at: " << file_path << endl;
        file.close(); // Close the file after creating it
    } else {
        cerr << "Failed to create empty file at: " << file_path << endl;
    }
    std::string new_folder_name = "./test_new_directory/";
    std::string new_file_name = "new_file_name.txt";
    fs::rename(test_directory, new_folder_name);
    cout << "rename folder: " << test_directory << " to new name:" << new_folder_name << endl;
    fs::rename(new_folder_name + filename, new_folder_name + new_file_name);
    cout << "rename file: " << new_folder_name + filename << " to new name:" << new_folder_name + new_file_name << endl;
    fs::rename(new_folder_name, test_directory);
    cout << "rename folder: " << new_folder_name << " back to name:" << test_directory << endl;
    fs::remove(test_directory.string() + new_file_name);
    cout << "remove file: " << test_directory.string() + new_file_name << endl;
    fs::remove(test_directory);
    cout << "remove folder: " << test_directory << endl;

    // 10. [[nodiscard]] attribute:
    get_no_discard_value(); // Compiler warning if the return value is discarded

    return 0;
}
#include <iostream>
#include <cstring>

class MyClass {
private:
    int& m_ref;
    const char* const_str;

public:
    // Constructor
    MyClass(int& ref, const char* str) : m_ref(ref), const_str(nullptr) {
        if (str != nullptr) {
            const_str = new char[std::strlen(str) + 1];
            std::strcpy(const_cast<char*>(const_str), str);
        }
    }

    // Destructor
    ~MyClass() {
        delete[] const_str;
    }

    // Copy constructor
    MyClass(const MyClass& other) : m_ref(other.m_ref), const_str(nullptr) {
        if (other.const_str != nullptr) {
            const_str = new char[std::strlen(other.const_str) + 1];
            std::strcpy(const_cast<char*>(const_str), other.const_str);
        }
    }

    // Copy assignment operator
    MyClass& operator=(const MyClass& other) {
        if (this != &other) { // Check for self-assignment
            // Clean up existing resource
            delete[] const_str;
            const_str = nullptr;

            // Copy from other
            if (other.const_str != nullptr) {
                const_str = new char[std::strlen(other.const_str) + 1];
                std::strcpy(const_cast<char*>(const_str), other.const_str);
            }
            
            m_ref = other.m_ref;
        }
        return *this;
    }

    // Print method
    void print() const {
        if (const_str != nullptr) {
            std::cout << "m_ref: " << m_ref << ", const_str: " << const_str << std::endl;
        } else {
            std::cout << "m_ref: " << m_ref << ", const_str is null" << std::endl;
        }
    }
};

int main() {
    int x = 10;
    const char* str = "Hello";
    MyClass obj1(x, str);
    obj1.print();

    MyClass obj2(obj1); // Copy constructor
    obj2.print();

    int y = 20;
    const char* str2 = "World";
    obj2 = MyClass(y, str2); // Copy assignment
    obj2.print();

    return 0;
}
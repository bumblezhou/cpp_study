#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <vector>

using namespace std;
using namespace std::chrono_literals;

class TestClass {
    public:
    static TestClass* getInstance() {
        if (test_class_inst == nullptr) {
            std::thread::id this_id = std::this_thread::get_id();
            cout << "thread:" << this_id << "-> Create Instance" << endl;
            test_class_inst = std::make_unique<TestClass>();   
        }
        return test_class_inst.get();
    }
    int add() {
        return a + b;
    }
    private:
    static std::unique_ptr<TestClass> test_class_inst;
    int a,b;
};
std::unique_ptr<TestClass> TestClass::test_class_inst = nullptr;

class Singleton {
public:
    static Singleton& getInstance() {
        static Singleton instance;
        return instance;
    }

private:
    Singleton() {} // Private constructor to prevent instantiation
    Singleton(const Singleton&) = delete; // Delete copy constructor
    Singleton& operator=(const Singleton&) = delete; // Delete assignment operator
    ~Singleton() {} // Private destructor to prevent delete by others
};

void thread_task() {
    auto inst1 = TestClass::getInstance();
    std::thread::id this_id = std::this_thread::get_id();
    cout << "thread:" << this_id << "->" << inst1 << endl;
}

void thread_task2() {
    std::thread::id this_id = std::this_thread::get_id();
    cout << "thread:" << this_id << "->" << &Singleton::getInstance() << endl;
}

int main()
{
    // std::vector<std::thread> thread_list1;
    // for (int i = 0; i < 20; i++) {
    //     thread_list1.push_back(std::thread(thread_task));
    // }

    // for (auto& thread : thread_list1) {
    //     if (thread.joinable()) {
    //         thread.join(); // Join or detach threads as needed
    //     }
    // }

    std::vector<std::thread> thread_list2;
    for (int i = 0; i < 20; i++) {
        thread_list2.push_back(std::thread(thread_task2));
    }

    for (auto& thread : thread_list2) {
        if (thread.joinable()) {
            thread.join(); // Join or detach threads as needed
        }
    }

    return 0;
}

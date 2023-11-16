#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

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

void thread_task() {
    auto inst1 = TestClass::getInstance();
    std::thread::id this_id = std::this_thread::get_id();
    cout << "thread:" << this_id << "->" << inst1 << endl;
}

int main()
{
    std::thread t1(thread_task);
    std::thread t2(thread_task);
    std::thread t3(thread_task);
    std::thread t4(thread_task);
    std::thread t5(thread_task);
    
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    
    // auto inst1 = TestClass::getInstance();
    // cout << inst1 << endl;
    
    // auto inst2 = TestClass::getInstance();
    // cout << inst2 << endl;
    
    // auto inst3 = TestClass::getInstance();
    // cout << inst3 << endl;

    return 0;
}

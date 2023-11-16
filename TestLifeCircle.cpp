#include <iostream>
#include <memory>
#include <thread>

using namespace std;

class TestDeviceInfo {
    public:
    TestDeviceInfo(int  v) : x(v) {
        cout << "x:" << x << ", TestDeviceInfo()" << endl;
    }
    ~TestDeviceInfo() {
        cout << "x:" << x << ", ~TestDeviceInfo()" << endl;
    }
    private:
    int x;
};

void thread_task(int v) {
    auto inst = std::make_unique<TestDeviceInfo>(v);
}


int main()
{
    static const auto inst1 = std::make_unique<TestDeviceInfo>(1);
    static const auto inst2 = std::make_unique<TestDeviceInfo>(2);
    
    std::thread t1(thread_task, 3);
    std::thread t2(thread_task, 4);
    
    t1.join();
    t2.join();
    
    thread_task(5);
    thread_task(6);

    static const auto inst7 = std::make_unique<TestDeviceInfo>(7);
    static const auto inst8 = std::make_unique<TestDeviceInfo>(8);

    return 0;
}


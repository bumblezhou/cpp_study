#include <iostream>
#include <mutex>
#include <map>
#include <thread>
#include <chrono>
#include <vector>

// Base class
class BaseClass
{
public:
    virtual void print() const = 0;
    virtual ~BaseClass() = default;
};

// Singleton factory calss
class SingletonFactory {
private:
    std::map<size_t, BaseClass*> instances_;
    std::mutex mutex_;
    SingletonFactory() {}
    SingletonFactory(const SingletonFactory&) = delete;
    SingletonFactory& operator=(const SingletonFactory&) = delete;
public:
    static SingletonFactory& getInstance() {
        static SingletonFactory instance;
        return instance;
    }

    template<typename T>
    T& createInstance() {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = instances_.find(typeid(T).hash_code());
        if (it == instances_.end()) {
            T* instance = new T();
            instances_[typeid(T).hash_code()] = instance;
            return *instance;
        }
        return *dynamic_cast<T*>(it->second);
    }

    ~SingletonFactory() {
        std::cout << "~SingletonFactory destructor..." << std::endl;
        for (auto &pair : instances_) {
            delete pair.second;
        }
        instances_.clear();
    }
};

// Example custom class
class MyClassA : public BaseClass {
public:
    MyClassA() {
        std::cout << "MyClassA created" << std::endl;
    }

    void print() const override {
        std::cout << "Hello from MyClassA with hash_code:" << typeid(MyClassA).hash_code() << std::endl;
    }

    ~MyClassA() {
        std::cout << "MyClassA released" << std::endl;
    }
};

// Example custom class
class MyClassB : public BaseClass {
public:
    MyClassB() {
        std::cout << "MyClassB created" << std::endl;
    }

    void print() const override {
        std::cout << "Hello from MyClassB with hash_code:" << typeid(MyClassB).hash_code() << std::endl;
    }

    ~MyClassB() {
        std::cout << "MyClassB released" << std::endl;
    }
};

void thread_task1() {
    MyClassA& instance1 = SingletonFactory::getInstance().createInstance<MyClassA>();
    instance1.print();
}

void thread_task2() {
    MyClassB& instance1 = SingletonFactory::getInstance().createInstance<MyClassB>();
    instance1.print();
}

int main() {
    std::vector<std::thread> thread_list;
    for (int i = 0; i < 20; i++) {
        thread_list.push_back(std::thread(thread_task1));
        thread_list.push_back(std::thread(thread_task2));
    }

    for (auto& thread : thread_list) {
        if (thread.joinable()) {
            thread.join(); // Join or detach threads as needed
        }
    }

    return 0;
}

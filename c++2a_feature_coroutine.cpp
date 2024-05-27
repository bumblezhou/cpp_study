#include <chrono>
#include <coroutine>
#include <functional>
#include <future>
#include <iostream>
#include <thread>

using namespace std;

// Promise
template<typename T>
struct Co {
    struct promise_type {
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

        auto await_transform(const std::function<T()>& work) {
            struct awaiter {
                std::future<T> m_future;
                std::thread m_t;
                bool await_ready() { return false; }
                void await_suspend(std::coroutine_handle<>) {}
                T await_resume() {
                    cout << "thread block? tid#" << std::this_thread::get_id() << endl;
                    return m_future.get();
                }
            };

            std::promise<T> p;
            std::future<T> f = p.get_future();
            std::thread t([work, p = std::move(p)]() mutable {
                cout << "[work]tid#" << std::this_thread::get_id() << endl;
                T value = work();
                p.set_value(value);
            });

            t.detach();

            return awaiter {
                std::move(f),
                std::move(t),
            };
        }

        T m_value = -1;
        void return_value(T value) {
            m_value = value;
            cout << "[promise_type] return_value" << endl;
        }
    };
    std::coroutine_handle<promise_type> handle;
    T Value() { return handle.promise().m_value; }
};

// coroutine
Co<int> run() {
    cout << "[run] before" << endl;
    int result = co_await []() {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return 42;
    };
    cout << "[run] after" << endl;
    co_return result;
}

int main() {
    auto co = run();
    while(!co.handle.done()) {
        co.handle.resume();
    }
    cout << "[main]" << co.Value() << endl;
    return 0;
}

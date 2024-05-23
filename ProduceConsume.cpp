#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>

// Message structure
struct Message {
    int id;
    std::string content;
};

// Message producer class
class MessageProducer {
public:
    MessageProducer(std::queue<Message>& queue, std::mutex& mutex, std::condition_variable& condition) 
        : queue(queue), mutex(mutex), condition(condition), nextId(0) {}

    void produceMessage(const std::string& content) {
        std::lock_guard<std::mutex> lock(mutex);
        queue.push({ nextId++, content });
        condition.notify_one();
    }

private:
    std::queue<Message>& queue;
    std::mutex& mutex;
    std::condition_variable& condition;
    int nextId;
};

// Message consumer class
class MessageConsumer {
public:
    MessageConsumer(std::queue<Message>& queue, std::mutex& mutex, std::condition_variable& condition) 
        : queue(queue), mutex(mutex), condition(condition) {}

    void consumeMessages() {
        bool running = true;
        while (running) {
            std::unique_lock<std::mutex> lock(mutex);
            condition.wait(lock, [this] { return !queue.empty(); });

            while (!queue.empty()) {
                Message message = queue.front();
                queue.pop();
                lock.unlock();

                // Process the message
                std::cout << "Consumed message: " << message.content << std::endl;
                if (message.content == "stop") {
                    running = false;
                }

                lock.lock();
            }
        }
    }

private:
    std::queue<Message>& queue;
    std::mutex& mutex;
    std::condition_variable& condition;
};

int main() {
    std::queue<Message> messageQueue;
    std::mutex mutex;
    std::condition_variable condition;

    MessageProducer producer(messageQueue, mutex, condition);
    MessageConsumer consumer(messageQueue, mutex, condition);

    // Start a thread to consume messages
    std::thread consumerThread([&consumer] { consumer.consumeMessages(); });

    // Start a thread to produce messages
    std::thread producerThread([&producer] {
        // Send messages
        for (int i = 0; i < 5; ++i) {
            producer.produceMessage("Message " + std::to_string(i));
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        producer.produceMessage("stop");
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    });

    // Wait for the consumer thread to finish
    consumerThread.join();

    // Wait for the producer thread to finish
    producerThread.join();

    return 0;
}
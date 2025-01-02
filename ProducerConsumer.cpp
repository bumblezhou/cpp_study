#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5

// 定义共享缓冲区
int buffer[BUFFER_SIZE];
int count = 0; // 当前缓冲区中的元素数量
int totalCount = 30; //总共需要处理的元素数量

// 互斥锁和条件变量
pthread_mutex_t mutex;
pthread_cond_t cond_producer;
pthread_cond_t cond_consumer;

// 生产者线程函数
void* producer(void* arg) {
    int data = 0;
    while (data < totalCount) {
        // 生产数据
        data++;
        sleep(1); // 模拟生产过程

        // 加锁访问共享缓冲区
        pthread_mutex_lock(&mutex);
        
        // 如果缓冲区满，则等待
        while (count == BUFFER_SIZE) {
            printf("Buffer full. Producer waiting...\n");
            pthread_cond_wait(&cond_producer, &mutex);
        }

        // 插入数据到缓冲区
        buffer[count] = data;
        printf("Produced: %d\n", data);
        count++;

        // 通知消费者缓冲区非空
        pthread_cond_signal(&cond_consumer);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

// 消费者线程函数
void* consumer(void* arg) {
    while (1) {
        int data;

        // 加锁访问共享缓冲区
        pthread_mutex_lock(&mutex);

        // 如果缓冲区空，则等待
        while (count == 0) {
            printf("Buffer empty. Consumer waiting...\n");
            pthread_cond_wait(&cond_consumer, &mutex);
        }

        // 从缓冲区取出数据
        data = buffer[count - 1];
        printf("Consumed: %d\n", data);
        count--;

        // 通知生产者缓冲区未满
        pthread_cond_signal(&cond_producer);
        pthread_mutex_unlock(&mutex);

        sleep(2); // 模拟消费过程
    }
    return NULL;
}

int main() {
    // 初始化互斥锁和条件变量
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_producer, NULL);
    pthread_cond_init(&cond_consumer, NULL);

    pthread_t producer_thread, consumer_thread;

    // 创建生产者和消费者线程
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // 等待线程结束
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // 销毁互斥锁和条件变量
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_producer);
    pthread_cond_destroy(&cond_consumer);

    return 0;
}

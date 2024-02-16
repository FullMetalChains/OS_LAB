// Implement a producer consumer problem without using semaphore//

#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>



const int BUFFER_SIZE = 5;
const int threadnumber = 1;

std::queue<int> buffer;
std::mutex mtx;
std::condition_variable not_full, not_empty;

void producer(int id) {
    for (int i = 0; i < 10; ++i) {
        std::unique_lock<std::mutex> lock(mtx);

        while (buffer.size() >= BUFFER_SIZE) {
            not_full.wait(lock);
        }

        int item = rand() % 100;
        buffer.push(item);
        std::cout << "Producer " << id << " produced: " << item << std::endl;

        not_empty.notify_all();
    }
}

void consumer(int id) {
    for (int i = 0; i < 10; ++i) {
        std::unique_lock<std::mutex> lock(mtx);

        while (buffer.empty()) {
            not_empty.wait(lock);
        }

        int item = buffer.front();
        buffer.pop();
        std::cout << "Consumer " << id << " consumed: " << item << std::endl;

        not_full.notify_all();
    }
}

int main() {
    std::vector<std::thread> producers;
    std::vector<std::thread> consumers;

    for (int i = 0; i < threadnumber; ++i) {
        producers.emplace_back(producer, i);
        consumers.emplace_back(consumer, i);
    }

    for (int i = 0; i < threadnumber; ++i) {
        producers[i].join();
        consumers[i].join();
    }

    return 0;
}
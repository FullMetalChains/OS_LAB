#include <iostream>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <queue>
#include <stdlib.h>

const int buffer_size = 5;
std::queue<int> buffer;
sem_t empty_slots, filled_slots;
pthread_mutex_t buffer_mutex;

void* producer(void* arg) {
    for (int i = 0; i < 10; ++i) {
        int item = rand()%100;
        sem_wait(&empty_slots);
        pthread_mutex_lock(&buffer_mutex);
        buffer.push(item);
        std::cout << "Producer produced item " << item << std::endl;
        pthread_mutex_unlock(&buffer_mutex);
        sem_post(&filled_slots);
    }
    return NULL;
}

void* consumer(void* arg) {
    for(int i = 0;i<10;i++){
        sem_wait(&filled_slots);
        pthread_mutex_lock(&buffer_mutex);
        int item = buffer.front();
        buffer.pop();
        std::cout << "Consumer consumed item " << item << std::endl;
        pthread_mutex_unlock(&buffer_mutex);
        sem_post(&empty_slots);
    }
    // pthead_exit(NULL);
    return NULL;
}

int main() {
    srand(time(0));
    pthread_t producer_thread;
    pthread_t consumer_thread;

    sem_init(&empty_slots, 0, buffer_size);
    sem_init(&filled_slots, 0, 0);
    pthread_mutex_init(&buffer_mutex, NULL);

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    sem_destroy(&empty_slots);
    sem_destroy(&filled_slots);
    pthread_mutex_destroy(&buffer_mutex);

    return 0;
}

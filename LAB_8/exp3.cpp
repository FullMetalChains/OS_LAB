#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>

// Shared memory structure
struct SharedData {
    int value;
    // You can add more data members as needed
};

int main() {
    // Key to identify the shared memory segment
    key_t key = ftok("shared_memory", 'R');
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Create a shared memory segment
    int shmid = shmget(key, sizeof(SharedData), 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Attach the shared memory segment
    SharedData *sharedData = (SharedData *)shmat(shmid, nullptr, 0);
    if ((intptr_t)sharedData == -1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Initialize shared data
    sharedData->value = 0;

    // Fork a child process
    pid_t childPid = fork();

    if (childPid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (childPid == 0) {
        // Child process
        for (int i = 0; i < 5; ++i) {
            sleep(1); // Simulate some work

            // Modify the shared data
            sharedData->value += 2;

            std::cout << "Child Process: Incremented shared value to " << sharedData->value << std::endl;
        }

        // Detach the shared memory segment
        if (shmdt(sharedData) == -1) {
            perror("shmdt");
            exit(EXIT_FAILURE);
        }
    } else {
        // Parent process
        for (int i = 0; i < 5; ++i) {
            sleep(1); // Simulate some work

            std::cout << "Parent Process: Current shared value is " << sharedData->value << std::endl;
        }

        // Wait for the child process to finish
        wait(NULL);

        // Detach and remove the shared memory segment
        if (shmdt(sharedData) == -1) {
            perror("shmdt");
            exit(EXIT_FAILURE);
        }

        if (shmctl(shmid, IPC_RMID, nullptr) == -1) {
            perror("shmctl");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
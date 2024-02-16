#include <iostream>
#include <mqueue.h>
#include <cstring>
#include <cstdlib>
#include <cerrno>
#include <syscall.h>
#include <unistd.h>

int main() {
    // Message queue attributes
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;      // Maximum number of messages in the queue
    attr.mq_msgsize = 1024;   // Maximum message size
    attr.mq_curmsgs = 0;

    // Open or create a message queue
    mqd_t mq = mq_open("/my_queue", O_CREAT | O_RDWR, 0666, &attr);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid > 0) { // Parent process
        // Send a message to the child
        const char* message_to_child = "Hello, child process!";
        if (mq_send(mq, message_to_child, strlen(message_to_child), 0) == -1) {
            perror("mq_send");
        }
    } else { // Child process
        // Receive a message from the parent
        char buffer[1024];
        unsigned int priority;
        int bytes_received = mq_receive(mq, buffer, sizeof(buffer), &priority);
        if (bytes_received == -1) {
            perror("mq_receive");
        } else {
            buffer[bytes_received] = '\0'; // Null-terminate the received data
            std::cout << "Child process received: " << buffer << std::endl;
        }
    }

    // Close and unlink the message queue
    mq_close(mq);
    mq_unlink("/my_queue");

    return 0;
}

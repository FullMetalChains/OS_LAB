//implement ipc using either pipes, message sharing or memory sharing
#include <iostream>
#include <unistd.h>
#include <string>

using namespace std;



int main(){
    int pipe_fd[2];
    if(pipe(pipe_fd) < 0){
        cout<<"Error\n";
        return 1;
    }
    pid_t child = fork();
    if(child > 0){
        //Parent process
        close(pipe_fd[0]);
        string message;
        cout<<"Enter message to be sent.\n";
        getline(cin, message);
        cout<<"Message process sent message: "<<message<<"\n";
        write(pipe_fd[1], message.c_str(), message.length());
        close(pipe_fd[1]);
    }
    else if(child == 0){
        // Child process
        close(pipe_fd[1]);
        char buffer[1024];
        int size = read(pipe_fd[0], buffer, sizeof(buffer));
        close(pipe_fd[0]);
        if(size > 0){
            buffer[size] = '\0';
            cout<<"Child process received message: "<<buffer<<"\n";
        }
    }
    else{
        cout<<"Error\n";
        return 1;
    }
}
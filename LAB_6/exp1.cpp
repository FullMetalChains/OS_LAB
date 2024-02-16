// Write a program to load a executable program in a child proces using execl system call

#include <iostream>
#include <unistd.h>
#include <string>

using namespace std;

int main(){
    pid_t pid = fork();
    if(pid == -1){
        perror("Fork error.\n");
    }
    else if(pid == 0){
        cout<<"Inside the child process.\n";
        char* args = "Ankan Nihar Jugya Spandan";
        cout<<"Executing execl on dummy_file.\n";
        execl("./dummy_file", "dummy_file", args, (char*)0);
        std::cout<<"Response not expected"<<"\n";
    }

}

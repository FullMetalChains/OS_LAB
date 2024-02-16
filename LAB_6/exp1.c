// Write a program to load a executable program in a child proces using execl system call


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
    pid_t pid = fork();
    if(pid == -1){
        perror("Fork error.\n");
    }
    else if(pid == 0){
        char* args[] = {"Ankan", "Nihar", "Priyabrat", "NULL"};
        execl("./dummy_file", "dummy_file", args, NULL);
        printf("Return not expected.\n");
    }


}

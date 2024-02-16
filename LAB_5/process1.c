#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>


// Write a program to create a new child process using fork system call

// int main()
// {
//     int x = 10;
//     pid_t child = fork();
//     if(child < 0){
//         printf("Process creation failed.\n");
//         exit(1);
//     }
//     else if(child == 0){
//         printf("Child process.\n");
//         printf("%d\n", getpid());
//         printf("%d\n", x);
//         printf("%d\n", getppid());
//     }
//     else{
//         printf("Parent process.\n");
//         printf("%d\n", getpid());
//         printf("%d\n", x);
//         printf("%d\n", getppid());
//     }
// }



//Implement the wait system call
//Write a program to block the parent process until child completes using wait system

int main()
{
    pid_t child = fork();
    if(child < 0){
        printf("Process creation failed.\n");
        exit(0);
    }
    else if(child == 0){
        printf("Child.\n");
        for(int i = 1;i<10;i+=2){
            printf("%d ",i);
        }
        printf("\n");
    }
    else{
        wait(NULL);
        printf("Parent.\n");
        for(int i = 2;i<=10;i+=2){
            printf("%d ", i);
        }
        printf("\n");
    }
}
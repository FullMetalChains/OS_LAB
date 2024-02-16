/*Write a program to display directory conetent using readdir system call*/

#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>

using namespace std;

int main(int argc, char* argv[]){
    DIR* d = opendir(argv[1]);
    if(d == NULL){
        cout<<"Couldn't find directory.\n"<<endl;
        exit(1);
    }
    struct dirent* entry;
    while((entry = readdir(d)) != NULL){
        cout<<entry->d_name<<endl;
    }
}
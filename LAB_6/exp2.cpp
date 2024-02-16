/*Write a program to display status using stat system call
st_id
link
size
st_mode - predefined mode, user permission
*/

#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <ctime>

using namespace std;

int main(int argc, char* argv[]){
    struct stat buffer;
    if(stat(argv[1], &buffer) == -1){
        cout<<"Error\n";
        return 0;
    }
    cout<<buffer.st_uid<<"\n";
    cout<<buffer.st_gid<<"\n";
    cout<<buffer.st_blksize<<"\n";
    cout<<buffer.st_blocks<<"\n";
    cout<<buffer.st_size<<"\n";
    cout<<buffer.st_nlink<<"\n";
    cout<<ctime(&buffer.st_atime);
    cout<<ctime(&buffer.st_mtime);
}
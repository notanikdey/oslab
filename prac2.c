#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>


int main(){
    int p;
    printf("\n%d\n\n", getpid());
    system("ps");
    p = fork();
    if(p==0){
        printf("\n This is the child process with ID %d", getpid());
        printf("\n");
        printf("\nIts Parent Process is %d",getppid());
        printf("\n");
        exit(0);
    }
    else{
        printf("\nThis is the parent process with ID %d",getpid());
    }
    puts("\nEnd\n");
    return 0;
}
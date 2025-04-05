#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>  
#include <sys/types.h> 
#include <sys/wait.h>
int main(){
    int x = fork();
    if(x==0){
        printf("Child Process \n");
        execlp("cat","cat","myfile.txt",NULL);

    }
    else{
        wait(NULL);
        printf("Parent Process \n");
    }
}
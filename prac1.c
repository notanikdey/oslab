/*Aim: Write a C program to read a file and copy the contents into a new file using system
calls like read(), write(), open() and close()*/

#include <stdio.h> 
#include <fcntl.h> 
#include <unistd.h> 

#define buffersize 10000


int main(){
    char source[25], dest[25];
    char buffer[buffersize];
    int read_in, write_out;
    printf("\n Enter Source File Name: ");
    scanf("%s",source);
    printf("Input File: %s", source);
    int sourcefile = open(source, O_RDONLY);
    if(sourcefile<0){
        printf("\n Source File Does Not Exist");
    }
    else{
        printf("\n Enter Destination File Name: ");
        scanf("%s", dest);
        int destfile = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        while((read_in = read(sourcefile,buffer, buffersize))>0){
            write_out = write(destfile, buffer, read_in);
        }
        close(sourcefile);
        close(destfile);
    }

    return 0;
}
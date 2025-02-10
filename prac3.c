#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h> 

int main() {
    int fd[2]; // File descriptors for pipe (fd[0] for reading, fd[1] for writing)
    
    if (pipe(fd) == -1) {
        perror("Pipe Failed");
        return 1;
    }

    __pid_t child_pid = fork();

    if (child_pid < 0) {
        perror("Fork Failed");
        return 1;
    }
    else if (child_pid == 0) { // Child process
        printf("Child process calculating length of name...\n");

        // Redirect stdin to read from the pipe
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]); // Close unused read end
        close(fd[1]); // Close unused write end

        execlp("wc", "wc", "-m", NULL); // Execute wc -m
        perror("execlp failed");
        return 1;
    }
    else { // Parent process
        printf("Parent Process waiting for the child...\n");

        close(fd[0]); // Close unused read end

        // Write data to the pipe
        write(fd[1], "Mohit", 5);
        close(fd[1]); // Close write end after writing

        wait(NULL); // Wait for child process
        printf("Child process has finished.\n");
    }

    return 0;
}

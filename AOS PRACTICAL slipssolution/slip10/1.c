/*Generate parent process to write unnamed pipe and will write into it. Also generate child process
which will read from pipe*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define BUFFER_SIZE 100

int main() {
    int pipe_fd[2]; // File descriptors for the pipe
    pid_t pid;

    if (pipe(pipe_fd) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // Parent process
        close(pipe_fd[0]); // Close unused read end

        char message[] = "Hello, child! This is the parent process writing to you.";
        printf("Parent process writing to pipe: %s\n", message);

        write(pipe_fd[1], message, sizeof(message)); // Write message to pipe

        close(pipe_fd[1]); // Close write end

        wait(NULL); // Wait for child to finish
    } else {
        // Child process
        close(pipe_fd[1]); // Close unused write end

        char buffer[BUFFER_SIZE];
        ssize_t bytes_read = read(pipe_fd[0], buffer, BUFFER_SIZE); // Read from pipe

        printf("Child process received from pipe: %.*s\n", (int)bytes_read, buffer);

        close(pipe_fd[0]); // Close read end
    }

    return 0;
}


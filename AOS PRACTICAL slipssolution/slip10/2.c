/*Write a program that illustrates how to execute two commands concurrently with a pipe.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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

        // Redirect stdout to the write end of the pipe
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]); // Close original write end

        // Execute the 'ls -l' command
        execlp("ls", "ls", "-l", NULL);
        perror("Exec failed in parent");
        exit(EXIT_FAILURE);
    } else {
        // Child process
        close(pipe_fd[1]); // Close unused write end

        // Redirect stdin to the read end of the pipe
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[0]); // Close original read end

        // Execute the 'grep .c' command
        execlp("grep", "grep", ".c", NULL);
        perror("Exec failed in child");
        exit(EXIT_FAILURE);
    }

    return 0;
}


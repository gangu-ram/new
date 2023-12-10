/*Write a C program to implement the following unix/linux command (use fork, pipe and exec
system call). Your program should block the signal Ctrl-C and Ctrl-\ signal during the execution.
i. ls –l | wc –l
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void sigHandler(int signum) {
    // Signal handler to handle SIGINT (Ctrl-C) and SIGQUIT (Ctrl-\)
    printf("Signal %d received and blocked.\n", signum);
}

int main() {
    signal(SIGINT, sigHandler); // Block Ctrl-C
    signal(SIGQUIT, sigHandler); // Block Ctrl-\

    int pipefd[2];
    pid_t pid;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        close(pipefd[0]); // Close unused read end

        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to pipe

        execlp("ls", "ls", "-l", NULL); // Execute ls -l
        perror("execlp");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        close(pipefd[1]); // Close unused write end

        dup2(pipefd[0], STDIN_FILENO); // Redirect stdin to pipe

        execlp("wc", "wc", "-l", NULL); // Execute wc -l
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    return 0;
}

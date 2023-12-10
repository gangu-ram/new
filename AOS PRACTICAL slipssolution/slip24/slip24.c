#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void childSignalHandler(int signum) {
    if (signum == SIGCHLD) {
        printf("Child process has terminated.\n");
    }
}

void alarmHandler(int signum) {
    if (signum == SIGALRM) {
        printf("Child process exceeded time limit. Killing...\n");
        exit(EXIT_FAILURE);
    }
}

int main() {
    pid_t pid;
    signal(SIGCHLD, childSignalHandler);
    signal(SIGALRM, alarmHandler);

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        // Replace "your_command_here" with the command or program you want to run
        execlp("your_command_here", "your_command_here", NULL);
        perror("Exec failed");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        alarm(5); // Set alarm for 5 seconds

        int status;
        waitpid(pid, &status, 0); // Wait for child process to complete

        alarm(0); // Cancel the alarm
    }

    return 0;
}


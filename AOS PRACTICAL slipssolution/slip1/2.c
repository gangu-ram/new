/*1
Write a C program to send SIGALRM signal by child process to parent process and parent process
make a provision to catch the signal and display alarm is fired.(Use Kill, fork, signal and sleep
system call)*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void alarmHandler(int signum) {
    if (signum == SIGALRM) {
        printf("Alarm is fired!\n");
    }
}

int main() {
    pid_t pid;
    signal(SIGALRM, alarmHandler);

    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        sleep(3); // Wait for 3 seconds
        kill(getppid(), SIGALRM); // Send SIGALRM signal to parent process
    } else {
        // Parent process
        while (1) {
            // Wait indefinitely for signals
            sleep(1);
        }
    }

    return 0;
}


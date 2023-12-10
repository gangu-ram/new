 /*Write a C program which creates a child process to run linux/ unix command or any user defined 
program. The parent process set the signal handler for death of child signal and Alarm signal. If 
a child process does not complete its execution in 5 second then parent process kills child process.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void child_handler(int signo) {
    if (signo == SIGCHLD) {
        printf("Child process terminated.\n");
        exit(EXIT_SUCCESS);
    }
}

void alarm_handler(int signo) {
    if (signo == SIGALRM) {
        printf("Timeout: Child process taking too long. Killing it.\n");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {  // Child process
        execvp(argv[1], &argv[1]); // Execute the command
        perror("Exec failed");
        exit(EXIT_FAILURE);
    } else {  // Parent process
        signal(SIGCHLD, child_handler); // Set signal handler for child termination
        signal(SIGALRM, alarm_handler); // Set signal handler for alarm

        // Set an alarm for 5 seconds
        alarm(5);

        // Wait for the child process to terminate
        wait(NULL);

        // Disable the alarm
        alarm(0);

        printf("Parent process exiting.\n");
    }

    return 0;
}


/* slip 16*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void childSignalHandler(int signum) {
    if (signum == SIGHUP) {
        printf("Child received SIGHUP signal.\n");
    } else if (signum == SIGINT) {
        printf("Child received SIGINT signal.\n");
    } else if (signum == SIGQUIT) {
        printf("My DADDY has Killed me!!!\n");
        exit(EXIT_SUCCESS);
    }
}

int main() {
    pid_t pid;
    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        signal(SIGHUP, childSignalHandler);
        signal(SIGINT, childSignalHandler);
        signal(SIGQUIT, childSignalHandler);

        while (1) {
            sleep(1);
        }
    } else {
        // Parent process
        int i;
        for (i = 0; i < 10; ++i) {
            sleep(3);
            if (i < 9) {
                kill(pid, SIGHUP); // Send SIGHUP every 3 seconds for 30 seconds
            } else {
                kill(pid, SIGQUIT); // Send SIGQUIT after 30 seconds
                wait(NULL); // Wait for child to terminate
            }
        }
    }

    return 0;
}

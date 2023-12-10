#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>

#define NUM_CHILDREN 5

int main() {
    pid_t pid;
    struct rusage usage;
    int status;
    int totalUserTime = 0;
    int totalKernelTime = 0;

    for (int i = 0; i < NUM_CHILDREN; ++i) {
        pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            // Perform child process operations here
            sleep(1); // For illustration, child processes sleep for 1 second
            exit(EXIT_SUCCESS);
        }
    }

    // Parent process
    while ((pid = wait(&status)) > 0) {
        if (getrusage(RUSAGE_CHILDREN, &usage) == -1) {
            perror("Error in getrusage");
            exit(EXIT_FAILURE);
        }

        totalUserTime += usage.ru_utime.tv_sec;
        totalKernelTime += usage.ru_stime.tv_sec;
    }

    printf("Total cumulative time spent in user mode by all children: %d seconds\n", totalUserTime);
    printf("Total cumulative time spent in kernel mode by all children: %d seconds\n", totalKernelTime);

    return 0;
}


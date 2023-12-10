//Write a C program that catches the ctrl-c (SIGINT) signal for the first time and display the
//appropriate message and exits on pressing ctrl-c again. 

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

// Variable to count the number of times SIGINT is received
int sigint_count = 0;

// Signal handler function
void handle_sigint(int signum) {
    if (signum == SIGINT) {
        if (sigint_count == 0) {
            printf("Ctrl+C pressed. Press again to exit.\n");
            sigint_count++;
        } else {
            printf("Exiting...\n");
            exit(EXIT_SUCCESS);
        }
    }
}

int main() {
    // Set up signal handler for SIGINT
    signal(SIGINT, handle_sigint);

    printf("Press Ctrl+C to trigger the signal handler.\n");

    // Infinite loop to keep the program running
    while (1) {
        // Do some work or just pause to keep the program running
        sleep(1);
    }

    return 0;
}


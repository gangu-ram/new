/* s11 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int file_desc = open("outpout.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (file_desc == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    int original_stdout = dup(STDOUT_FILENO); // Save the original STDOUT

    if (dup2(file_desc, STDOUT_FILENO) == -1) {
        perror("dup2");
        exit(EXIT_FAILURE);
    }

    // Your output
    printf("This output will be redirected to outpout.txt\n");

    if (dup2(original_stdout, STDOUT_FILENO) == -1) {
        perror("dup2");
        exit(EXIT_FAILURE);
    }

    close(file_desc); // Close the file descriptor

    return 0;
}

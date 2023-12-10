/*Q.2) Write a C program which receives file names as command line arguments and display those
filenames in ascending order according to their sizes. I) (e.g $ a.out a.txt b.txt c.txt, ...)*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

// Function to compare file sizes for qsort
int compareFileSizes(const void *a, const void *b) {
    struct stat *statA = (struct stat *)a;
    struct stat *statB = (struct stat *)b;

    return (int)(statA->st_size - statB->st_size);
}

int main(int argc, char *argv[]) {
    // Check if there are enough command line arguments
    if (argc < 2) {
        fprintf(stderr, "Usage: %s file1 file2 file3 ...\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Allocate an array of stat structures to store file information
    struct stat *fileStats = (struct stat *)malloc((argc - 1) * sizeof(struct stat));
    if (!fileStats) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    // Get file information for each file
    for (int i = 1; i < argc; i++) {
        if (stat(argv[i], &fileStats[i - 1]) == -1) {
            perror("Error getting file information");
            free(fileStats);
            exit(EXIT_FAILURE);
        }
    }

    // Sort the file names based on their sizes
    qsort(fileStats, argc - 1, sizeof(struct stat), compareFileSizes);

    // Display the sorted file names
    printf("File names sorted by size:\n");
    for (int i = 0; i < argc - 1; i++) {
        printf("%s\n", argv[i + 1]);
    }

    // Free allocated memory
    free(fileStats);

    return 0;
}


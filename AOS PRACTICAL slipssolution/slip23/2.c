#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void identifyFileType(const char *filename) {
    struct stat fileInfo;

    if (stat(filename, &fileInfo) == -1) {
        perror("Error in stat");
        return;
    }

    printf("File: %s\n", filename);

    if (S_ISREG(fileInfo.st_mode)) {
        printf("Type: Regular File\n");
    } else if (S_ISDIR(fileInfo.st_mode)) {
        printf("Type: Directory\n");
    } else if (S_ISCHR(fileInfo.st_mode)) {
        printf("Type: Character Device\n");
    } else if (S_ISBLK(fileInfo.st_mode)) {
        printf("Type: Block Device\n");
    } else if (S_ISFIFO(fileInfo.st_mode)) {
        printf("Type: FIFO/pipe\n");
    } else if (S_ISLNK(fileInfo.st_mode)) {
        printf("Type: Symbolic Link\n");
    } else if (S_ISSOCK(fileInfo.st_mode)) {
        printf("Type: Socket\n");
    } else {
        printf("Type: Unknown\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    identifyFileType(argv[1]);

    return 0;
}


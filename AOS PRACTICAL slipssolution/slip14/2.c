#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

void printFileProperties(const char *filename) {
    struct stat fileInfo;

    if (stat(filename, &fileInfo) == -1) {
        perror("Error in stat");
        return;
    }

    printf("File: %s\n", filename);
    printf("Inode number: %ld\n", (long)fileInfo.st_ino);
    printf("Number of hard links: %ld\n", (long)fileInfo.st_nlink);
    printf("File size: %ld bytes\n", (long)fileInfo.st_size);

    printf("File permissions: ");
    printf((S_ISDIR(fileInfo.st_mode)) ? "d" : "-");
    printf((fileInfo.st_mode & S_IRUSR) ? "r" : "-");
    printf((fileInfo.st_mode & S_IWUSR) ? "w" : "-");
    printf((fileInfo.st_mode & S_IXUSR) ? "x" : "-");
    printf((fileInfo.st_mode & S_IRGRP) ? "r" : "-");
    printf((fileInfo.st_mode & S_IWGRP) ? "w" : "-");
    printf((fileInfo.st_mode & S_IXGRP) ? "x" : "-");
    printf((fileInfo.st_mode & S_IROTH) ? "r" : "-");
    printf((fileInfo.st_mode & S_IWOTH) ? "w" : "-");
    printf((fileInfo.st_mode & S_IXOTH) ? "x\n" : "-\n");

    printf("Owner: %s\n", getpwuid(fileInfo.st_uid)->pw_name);
    printf("Group: %s\n", getgrgid(fileInfo.st_gid)->gr_name);

    printf("Last access time: %s", ctime(&fileInfo.st_atime));
    printf("Last modification time: %s", ctime(&fileInfo.st_mtime));
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    printFileProperties(argv[1]);

    return 0;
}


#include <stdio.h>
#include <dirent.h>
#include <string.h>

void findFiles(const char *prefix) {
    struct dirent *entry;
    DIR *dp;

    dp = opendir(".");
    if (dp == NULL) {
        perror("Failed to open directory");
        return;
    }

    printf("Files beginning with '%s':\n", prefix);

    while ((entry = readdir(dp)) != NULL) {
        if (strncmp(prefix, entry->d_name, strlen(prefix)) == 0) {
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dp);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <prefix>\n", argv[0]);
        return 1;
    }

    findFiles(argv[1]);

    return 0;
}


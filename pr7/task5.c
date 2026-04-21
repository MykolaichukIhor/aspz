#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

void list_files_recursively(const char *base_path) {
    char path[1024];
    struct dirent *dp;
    DIR *dir = opendir(base_path);

    if (!dir) return;

    while ((dp = readdir(dir)) != NULL) {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
            
            snprintf(path, sizeof(path), "%s/%s", base_path, dp->d_name);
            
            struct stat statbuf;
            if (stat(path, &statbuf) == 0) {
                if (S_ISDIR(statbuf.st_mode)) {
                    // Якщо це директорія, рекурсивно заходимо в неї
                    list_files_recursively(path);
                } else {
                    
                    printf("%s\n", path);
                }
            }
        }
    }
    closedir(dir);
}

int main() {
    printf("Файли у поточному каталозі та підкаталогах:\n");
    list_files_recursively(".");
    return 0;
}
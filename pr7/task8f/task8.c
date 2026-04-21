#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main() {
    DIR *dir = opendir(".");
    struct dirent *entry;
    struct stat statbuf;
    char response[10];

    if (!dir) {
        perror("Помилка відкриття директорії");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        if (stat(entry->d_name, &statbuf) == 0 && S_ISREG(statbuf.st_mode)) {
            printf("Видалити файл '%s'? (y/n): ", entry->d_name); // Запит імені файлу [cite: 67]
            
            if (fgets(response, sizeof(response), stdin) != NULL) {
                if (response[0] == 'y' || response[0] == 'Y') {
                    if (unlink(entry->d_name) == 0) {
                        printf("Файл видалено.\n");
                    } else {
                        perror("Помилка видалення");
                    }
                } else {
                    printf("Пропущено.\n");
                }
            }
        }
    }
    closedir(dir);
    return 0;
}
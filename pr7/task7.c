#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

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
        
        char *ext = strrchr(entry->d_name, '.');
        if (ext && strcmp(ext, ".c") == 0) {
            
            if (stat(entry->d_name, &statbuf) == 0 && S_ISREG(statbuf.st_mode)) {
                printf("Знайдено вихідний файл: %s\n", entry->d_name);
                printf("Надати іншим дозвіл на читання? (y/n): ");
                
                if (fgets(response, sizeof(response), stdin) != NULL) {
                    if (response[0] == 'y' || response[0] == 'Y') {
                        // Додаємо право S_IROTH (Read for Others)
                        mode_t new_mode = statbuf.st_mode | S_IROTH;
                        if (chmod(entry->d_name, new_mode) == 0) {
                            printf("Дозвіл надано.\n\n");
                        } else {
                            perror("Помилка chmod");
                        }
                    } else {
                        printf("Пропущено.\n\n");
                    }
                }
            }
        }
    }
    closedir(dir);
    return 0;
}
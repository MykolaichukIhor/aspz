#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
   
    if (argc != 3) {
        fprintf(stderr, "Використання: %s <слово> <файл>\n", argv[0]);
        return 1;
    }

    const char *word = argv[1];
    FILE *file = fopen(argv[2], "r");
    
    if (!file) {
        perror("Помилка відкриття файлу");
        return 1;
    }

    char line[2048];

    while (fgets(line, sizeof(line), file) != NULL) {
        
        if (strstr(line, word) != NULL) {
            printf("%s", line);
        }
    }

    fclose(file);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

void print_file_paginated(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror(filename);
        return;
    }

    
    FILE *tty = fopen("/dev/tty", "r");
    if (!tty) tty = stdin;

    char line[2048];
    int line_count = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
        line_count++;

        
        if (line_count == 20) {
            printf("\n--- Натисніть Enter для продовження ---\n");
            fgetc(tty); 
            line_count = 0;
        }
    }
    
    if (tty != stdin) fclose(tty);
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Використання: %s <файл1> [файл2 ...]\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        printf("=== %s ===\n", argv[i]);
        print_file_paginated(argv[i]);
    }

    return 0;
}
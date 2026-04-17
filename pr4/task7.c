#include <stdio.h>
#include <stdlib.h>

struct sbar {
    int x;
    double y;
};

int main() {
    struct sbar *ptr, *newptr;


    ptr = calloc(1000, sizeof(struct sbar));
    if (!ptr) {
        perror("calloc failed");
        return 1;
    }

    printf("calloc done\n");

    
    newptr = realloc(ptr, 500 * sizeof(struct sbar));
    if (!newptr) {
        perror("realloc failed");
        free(ptr);
        return 1;
    }

    ptr = newptr;
    printf("realloc done\n");

    newptr = reallocarray(ptr, 2000, sizeof(struct sbar));
    if (!newptr) {
        perror("reallocarray failed");
        free(ptr);
        return 1;
    }

    ptr = newptr;
    printf("reallocarray done\n");

    free(ptr);
    return 0;
}
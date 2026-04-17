#include <stdio.h>
#include <stdlib.h>

int main() {
    void *ptr = malloc(1024);
    void *tmp;

    tmp = realloc(ptr, (size_t)1e15); // дуже великий розмір

    if (tmp == NULL) {
        printf("realloc failed, ptr still valid\n");
        free(ptr);
    } else {
        ptr = tmp;
        free(ptr);
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

int main() {
    void *ptr = NULL;
    for (int i = 0; i < 3; i++) {
        if (!ptr)
            ptr = malloc(10);

        printf("Using ptr: %p\n", ptr);

        free(ptr);
        ptr = NULL; // fix
    }
    return 0;
}
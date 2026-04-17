#include <stdio.h>
#include <stdlib.h>

int main() {
    void *p = malloc(0);

    if (p == NULL)
        printf("NULL returned\n");
    else
        printf("Non-NULL pointer: %p\n", p);

    free(p);
    return 0;
}
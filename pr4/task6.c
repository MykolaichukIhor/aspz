#include <stdio.h>
#include <stdlib.h>

int main() {
    void *p1 = realloc(NULL, 100); // як malloc
    printf("p1 = %p\n", p1);

    void *p2 = realloc(p1, 0); // як free
    printf("p2 = %p\n", p2);

    return 0;
}
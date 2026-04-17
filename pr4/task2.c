#include <stdio.h>
#include <stdlib.h>

int main() {
    int xa = 1000000;
    int xb = 1000000;
    int num = xa * xb; // переповнення

    printf("num = %d\n", num);

    void *p = malloc(num);
    if (p == NULL) {
        printf("malloc failed\n");
    } else {
        printf("malloc succeeded\n");
        free(p);
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    volatile double x = 0.0;

    printf("Starting CPU stress...\n");


    for (long long i = 0; i < 1e9; i++) {
        x += i * 0.000001;
    }

    printf("Done. Result = %f\n", x);
    return 0;
}
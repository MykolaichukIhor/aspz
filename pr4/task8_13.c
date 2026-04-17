#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SMALL_BLOCKS 200000
#define SMALL_SIZE 1024
#define LARGE_SIZE (200 * 1024 * 1024)

void pause_and_show(const char *msg) {
    printf("\n%s\n", msg);
    printf("PID: %d\n", getpid());
    printf("Press Enter to continue...\n");
    getchar();
}

int main() {
    // великй блок
    void *big = malloc(LARGE_SIZE);
    pause_and_show("After allocating 200MB");

    free(big);
    pause_and_show("After freeing 200MB");

    // багато малих блоків
    void *arr[SMALL_BLOCKS];
    for (int i = 0; i < SMALL_BLOCKS; i++) {
        arr[i] = malloc(SMALL_SIZE);
    }
    pause_and_show("After allocating many small blocks");

    for (int i = 0; i < SMALL_BLOCKS; i++) {
        free(arr[i]);
    }
    pause_and_show("After freeing small blocks");

    return 0;
}
// leak_service.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define CHUNK_SIZE (1024 * 1024) // 1 MB

int main() {
    printf("Leak service started (PID: %d)\n", getpid());

    size_t total_allocated = 0;

    while (1) {
        void *ptr = malloc(CHUNK_SIZE);
        if (!ptr) {
            perror("malloc failed");
            break;
        }

        memset(ptr, 0, CHUNK_SIZE);

        total_allocated += CHUNK_SIZE;
        printf("Allocated: %zu MB\n", total_allocated / (1024 * 1024));

        sleep(1);
    }

    return 0;
}
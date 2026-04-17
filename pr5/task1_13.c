#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define SIZE (100 * 1024 * 1024) // 100 MB

int main() {
    char *mem = malloc(SIZE);
    if (!mem) {
        perror("malloc");
        return 1;
    }

    
    memset(mem, 0, SIZE);

    printf("PID батька: %d\n", getpid());
    printf("RSS перед fork():\n");
    getchar();

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
       
        printf("PID дитини: %d\n", getpid());
        printf("Після fork(), до змін (COW ще не спрацював):\n");
        getchar();

       
        mem[0] = 1;

        printf("Після зміни 1 байта (COW спрацював):\n");
        getchar();

        free(mem);
    } else {
        wait(NULL);
        free(mem);
    }

    return 0;
}
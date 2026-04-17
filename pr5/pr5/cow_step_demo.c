#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/mman.h>

#define SIZE (90 * 1024 * 1024)
#define PAGE_SIZE 4096

void touch_range(char *ptr, size_t start, size_t end) {
    for (size_t i = start; i < end; i++) {
        volatile char *p = ptr + i * PAGE_SIZE;
        *p = 1;   // FORCE page fault + COW break
    }
}

void print(pid_t pid, const char *msg) {
    printf("\n%s\n", msg);
    char cmd[256];
    snprintf(cmd, sizeof(cmd),
             "ps -o pid,rss,vsz -p %d",
             pid);
    system(cmd);
}

int main() {
    printf("===RSS INCREASE===\n");
    printf("Total memory: 90 MB\n");
    printf("Page size: 4 KB\n");
    printf("Total pages: %zu\n\n", SIZE / PAGE_SIZE);

    char *mem = mmap(NULL, SIZE,
                     PROT_READ | PROT_WRITE,
                     MAP_PRIVATE | MAP_ANONYMOUS,
                     -1, 0);

    if (mem == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    pid_t pid = fork();

    if (pid == 0) {
        size_t pages = SIZE / PAGE_SIZE;

        printf("\n[CHILD] PID: %d\n", getpid());

        printf("\nBEFORE TOUCH (after fork):\n");
        print(getpid(), "RSS:");

        printf("\nPress ENTER...\n");
        getchar();


        size_t step = pages / 4;

        touch_range(mem, 0, step);
        print(getpid(), "STEP 1 (25%)");

        getchar();

        touch_range(mem, step, step * 2);
        print(getpid(), "STEP 2 (50%)");

        getchar();


        touch_range(mem, step * 2, step * 3);
        print(getpid(), "STEP 3 (75%)");

        getchar();

        // STEP 4
        touch_range(mem, step * 3, pages);
        print(getpid(), "STEP 4 (100%)");

        getchar();

        munmap(mem, SIZE);
        printf("\nChild exit\n");

    } else if (pid > 0) {

        printf("\n[PARENT] PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);

        printf("\nParent should stay stable:\n");
        print(getpid(), "PARENT RSS:");

        wait(NULL);

        munmap(mem, SIZE);
    } else {
        perror("fork");
        return 1;
    }

    return 0;
}
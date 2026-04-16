#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <sys/resource.h>

void handler(int sig) {
    printf("\n=== STOP: Перевищено максимальний розмір файлу! ===\n");
    exit(1);
}

long get_file_size(FILE *f) {
    long current = ftell(f);
    return current;
}

int main() {
    struct rlimit rl;
    rl.rlim_cur = 1024; 
    rl.rlim_max = 1024;

    setrlimit(RLIMIT_FSIZE, &rl);

    signal(SIGXFSZ, handler);

    FILE *f = fopen("dice.txt", "w");
    if (!f) {
        perror("fopen");
        return 1;
    }

    srand(time(NULL));

    int step = 0;

    while (1) {
        int dice = rand() % 6 + 1;

        fprintf(f, "%d\n", dice);
        fflush(f);

        step++;

        long size = get_file_size(f);

        printf("Крок: %d | Значення: %d | Розмір файлу: %ld байт\n",
               step, dice, size);

    }

    fclose(f);
    return 0;
}
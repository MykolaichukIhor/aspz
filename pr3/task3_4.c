#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <time.h>

void cpu_limit_handler(int sig) {
    printf("\nПеревищено ліміт CPU часу!\n");
    exit(1);
}

int exists(int arr[], int size, int x) {
    for (int i = 0; i < size; i++)
        if (arr[i] == x) return 1;
    return 0;
}

void generate_unique(int *arr, int size, int max) {
    for (int i = 0; i < size; ) {
        int num = rand() % max + 1;
        if (!exists(arr, i, num)) {
            arr[i] = num;
            i++;
        }
    }
}

int main() {

    while(1) {
    srand(time(NULL));

    struct rlimit rl;
    rl.rlim_cur = 1;
    rl.rlim_max = 1;
    setrlimit(RLIMIT_CPU, &rl);

    signal(SIGXCPU, cpu_limit_handler);

    int set1[7];
    int set2[6];

    generate_unique(set1, 7, 49);
    generate_unique(set2, 6, 36);

    printf("7 з 49: ");
    for (int i = 0; i < 7; i++)
        printf("%d ", set1[i]);

    printf("\n6 з 36: ");
    for (int i = 0; i < 6; i++)
        printf("%d ", set2[i]);

    printf("\n");

    }




    return 0;
}
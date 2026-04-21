#include <stdio.h>
#include <stdlib.h>
#include <time.h>


unsigned long long comparisons = 0;


int compare(const void *a, const void *b) {
    comparisons++;
    int int_a = *((int*)a);
    int int_b = *((int*)b);
    if (int_a < int_b) return -1;
    if (int_a > int_b) return 1;
    return 0;
}


void generate_random(int *arr, int size) {
    for (int i = 0; i < size; i++) arr[i] = rand() % size;
}

void generate_sorted(int *arr, int size) {
    for (int i = 0; i < size; i++) arr[i] = i;
}

void generate_reverse(int *arr, int size) {
    for (int i = 0; i < size; i++) arr[i] = size - i;
}

void generate_identical(int *arr, int size) {
    for (int i = 0; i < size; i++) arr[i] = 42;
}

void generate_v_shape(int *arr, int size) {
    int mid = size / 2;
    for (int i = 0; i < mid; i++) arr[i] = mid - i;
    for (int i = mid; i < size; i++) arr[i] = i - mid;
}


void run_experiment(const char *name, void (*gen_func)(int*, int), int size) {
    int *arr = malloc(size * sizeof(int));
    if (!arr) return;

    gen_func(arr, size);
    
    comparisons = 0;
    clock_t start = clock();
    qsort(arr, size, sizeof(int), compare);
    clock_t end = clock();

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("%-20s | %12llu | %8.5f сек\n", name, comparisons, time_spent);
    free(arr);
}

int main() {
    srand(time(NULL));
    int size = 1000000; 

    printf("Розмір масиву: %d елементів\n", size);
    printf("------------------------------------------------------\n");
    printf("%-20s | %12s | %s\n", "Тип масиву", "Порівняння", "Час");
    printf("------------------------------------------------------\n");

    run_experiment("Випадкові числа", generate_random, size);
    run_experiment("Вже відсортований", generate_sorted, size);
    run_experiment("Зворотній порядок", generate_reverse, size);
    run_experiment("Всі однакові", generate_identical, size);
    run_experiment("V-подібний", generate_v_shape, size);
    
    printf("------------------------------------------------------\n");
    return 0;
}
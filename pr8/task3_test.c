#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}


bool is_sorted_correctly(int *original, int *sorted, int size) {
    long long sum_orig = 0, sum_sorted = 0;

    for (int i = 0; i < size; i++) {
        sum_orig += original[i];
        sum_sorted += sorted[i];
        
        
        if (i > 0 && sorted[i] < sorted[i - 1]) {
            return false; // Порушено порядок
        }
    }
    
    
    return sum_orig == sum_sorted;
}


void run_test(const char *test_name, int *data, int size) {
    int *copy = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) copy[i] = data[i];

    qsort(copy, size, sizeof(int), cmp);

    if (is_sorted_correctly(data, copy, size)) {
        printf("[PASS] %s\n", test_name);
    } else {
        printf("[FAIL] %s\n", test_name);
    }

    free(copy);
}

int main() {
    printf("Запуск тестів для функції qsort:\n");

    
    int test1[] = {5, 2, 9, 1, 5, 6};
    run_test("Звичайний масив", test1, 6);

    
    int test2[] = {};
    run_test("Порожній масив", test2, 0);

    
    int test3[] = {42};
    run_test("Один елемент", test3, 1);

    
    int test4[] = {7, 7, 7, 7, 7};
    run_test("Всі однакові елементи", test4, 5);

    
    int test5[] = {1, 2, 3, 4, 5, 6};
    run_test("Відсортований масив", test5, 6);

    
    int test6[] = {10, 5, 0, -5, -10};
    run_test("Від'ємні числа та зворотній порядок", test6, 5);

    
    int test7[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    run_test("Елементи, що дублюються", test7, 11);

    return 0;
}
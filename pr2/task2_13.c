#include <stdio.h>

int data_array[500] = {1, 2, 3, 4, 5}; 

int bss_array[1000];

void math_logic() {
    int sum = 0;
    for (int i = 0; i < 1000; i++) {
        sum += i * 2;
        if (i % 2 == 0) {
            bss_array[i] = sum;
        }
    }
    printf("Логіка виконана. Сума: %d\n", sum);
}

int main() {
    printf("Перший елемент даних: %d\n", data_array[0]);
    math_logic();
    return 0;
}
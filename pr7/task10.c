#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main() {
    
    srand(time(NULL) ^ getpid()); 

    double n;
    printf("Введіть значення n: ");
    if (scanf("%lf", &n) != 1) {
        printf("Помилка вводу.\n");
        return 1;
    }

    printf("\nВипадкові числа:\n");
    for (int i = 0; i < 5; i++) {
        
        double rand_0_1 = (double)rand() / RAND_MAX;
        
        
        double rand_0_n = rand_0_1 * n;

        printf("Від 0.0 до 1.0: %f\t | Від 0.0 до %.2f: %f\n", rand_0_1, n, rand_0_n);
    }

    return 0;
}
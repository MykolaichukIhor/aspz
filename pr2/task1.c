#include <stdio.h>
#include <time.h>

int main() {
    
    time_t max_time = (time_t)(((unsigned long long)1 << (sizeof(time_t) * 8 - 1)) - 1);

    printf("Розмір time_t у цій системі: %zu байт(ів)\n", sizeof(time_t));
    printf("Максимальне значення time_t: %lld секунд\n", (long long)max_time);

    struct tm *time_info = gmtime(&max_time);

    if (time_info != NULL) {
        printf("Момент закінчення/переповнення (UTC): %s\n", asctime(time_info));
    } else {
        printf("Функція gmtime() не змогла конвертувати це значення (дата занадто далека для структури tm).\n\n");
    }

    
    time_t y2k38_max = 2147483647; 
    printf("--- Демонстрація Проблеми 2038 року ---\n");
    printf("Час перед переповненням (2147483647): %s", asctime(gmtime(&y2k38_max)));
    
    y2k38_max += 100; 
    printf("Час ПІСЛЯ переповнення (2147483648): %s", asctime(gmtime(&y2k38_max)));

    return 0;
}
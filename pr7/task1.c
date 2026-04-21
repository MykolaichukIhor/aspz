#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *rwho_fp = popen("who", "r");
    if (!rwho_fp) {
        perror("Помилка popen для rwho");
        return 1;
    }

  
    FILE *more_fp = popen("more", "w");
    if (!more_fp) {
        perror("Помилка popen для more");
        pclose(rwho_fp);
        return 1;
    }

    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), rwho_fp) != NULL) {
        fputs(buffer, more_fp);
    }

    // Закриваємо потоки
    pclose(rwho_fp);
    pclose(more_fp);
    
    return 0;
}
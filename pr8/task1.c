#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main() {
    int fd[2];
    
    
    if (pipe(fd) == -1) {
        perror("Помилка створення pipe");
        return 1;
    }

    
    int flags = fcntl(fd[1], F_GETFL, 0);
    
    
    if (fcntl(fd[1], F_SETFL, flags | O_NONBLOCK) == -1) {
        perror("Помилка fcntl");
        return 1;
    }

    
    size_t nbytes = 1024 * 1024; 
    char *buffer = malloc(nbytes);
    
    if (buffer == NULL) {
        perror("Помилка виділення пам'яті");
        return 1;
    }

    printf("Спроба записати %zu байтів у pipe...\n", nbytes);
    
    
    ssize_t count = write(fd[1], buffer, nbytes);

    if (count == -1) {
        perror("Помилка write");
    } else {
        printf("Запрошено до запису (nbytes): %zu байтів\n", nbytes);
        printf("Фактично записано (count):  %zd байтів\n", count);
        
        if (count != (ssize_t)nbytes) {
            printf("\n=> Демонстрація успішна! count (%zd) відрізняється від nbytes (%zu).\n", count, nbytes);
        }
    }

    
    free(buffer);
    close(fd[0]);
    close(fd[1]);
    
    return 0;
}
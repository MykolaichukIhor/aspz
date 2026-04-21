#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    
    unsigned char data[] = {4, 5, 2, 2, 3, 3, 7, 9, 1, 5};
    const char *filename = "test_file.bin";

    
    int fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Помилка відкриття файлу");
        return 1;
    }

    
    if (write(fd, data, sizeof(data)) != sizeof(data)) {
        perror("Помилка запису у файл");
        close(fd);
        return 1;
    }

    
    if (lseek(fd, 3, SEEK_SET) == -1) {
        perror("Помилка lseek");
        close(fd);
        return 1;
    }

    
    unsigned char buffer[4];
    ssize_t bytes_read = read(fd, buffer, 4);

    if (bytes_read == -1) {
        perror("Помилка read");
    } else {
        
        printf("Прочитано байтів: %zd\n", bytes_read);
        printf("Вміст буфера: ");
        for (int i = 0; i < bytes_read; i++) {
            printf("%d ", buffer[i]);
        }
        printf("\n");
    }

   
    close(fd);
   // unlink(filename);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include <sys/wait.h>

#define FILE_SIZE (3 * 1024 * 1024) 
#define FILENAME "shared_test.txt"

int main() {

    int fd = open(FILENAME, O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd == -1) { perror("open"); return 1; }
    
    char init_data[FILE_SIZE];
    memset(init_data, ' ', FILE_SIZE);
    write(fd, init_data, FILE_SIZE);

    
    char *map = mmap(NULL, FILE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) { perror("mmap"); close(fd); return 1; }

    
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return 1;
    } 
    else if (pid == 0) {
        
        for (int i = 0; i < FILE_SIZE; i++) {
            map[i] = 'M'; 
        }
        
        msync(map, FILE_SIZE, MS_SYNC);
        exit(0);
    } 
    else {
        
        char write_buf[FILE_SIZE];
        memset(write_buf, 'W', FILE_SIZE); 
        
        
        lseek(fd, 0, SEEK_SET);
        write(fd, write_buf, FILE_SIZE);
        
        
        wait(NULL);
    }


    munmap(map, FILE_SIZE);
    close(fd);

    printf("Експеримент завершено. Перевірте вміст файлу: cat %s\n", FILENAME);
    return 0;
}
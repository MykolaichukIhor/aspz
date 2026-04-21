#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int main() {
    struct timeval start, end;
    long mtime, seconds, useconds;

    
    gettimeofday(&start, NULL);

    
    printf("Виконується робота...\n");
    sleep(1); 
    for(volatile int i = 0; i < 10000000; i++); 

    
    gettimeofday(&end, NULL);

    seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;

    
    mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;

    printf("Час виконання: %ld мілісекунд\n", mtime);

    return 0;
}
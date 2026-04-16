#include <stdio.h>

void recurse(int depth) {
    int buffer[1024]; 

    printf("Depth: %d\n", depth);


    for (int i = 0; i < 1024; i++) {
        buffer[i] = i;
    }

    recurse(depth + 1); 
}

int main() {
    printf("Start recursion\n");
    recurse(1);
    return 0;
}
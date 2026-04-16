#include <stdio.h>

void recurse(int i) {
    char buffer[1024];
    printf("%d\n", i);
    recurse(i + 1);
}

int main() {
    recurse(0);
    return 0;
}
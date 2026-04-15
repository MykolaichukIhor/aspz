#include <stdio.h>

int main() {
    int local_uninit[1000];
    int local_init[1000] = {1};
    
    printf("Hello, World!\n");
    return 0;
}

// 1
// #include <stdio.h>

// int main() {
//     printf("Hello, World!\n");
//     return 0;
// }

// 2 

// #include <stdio.h>

// int global_array[1000]; // неініціалізований масив

// int main() {
//     printf("Hello, World!\n");
//     return 0;
// }


// 3 


// #include <stdio.h>

// int main() {
//     int local_uninit[1000];
//     int local_init[1000] = {1};
    
//     printf("Hello, World!\n");
//     return 0;
// }



// 4

// #include <stdio.h>

// int main() {
//     int local_uninit[1000];
//     int local_init[1000] = {1};
    
//     printf("Hello, World!\n");
//     return 0;
// }
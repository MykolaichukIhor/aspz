#include <stdio.h>
#include <stdlib.h>


int global_init_var = 42;


int global_uninit_var;


void grow_stack() {


    int large_array[10000]; 
    
    
    large_array[0] = 1; 
    
    printf("Вершина стека ПІСЛЯ виклику функції: %p\n", (void*)&large_array[0]);
}

int main() {

    int local_var; 
    
  
    int *heap_ptr = malloc(sizeof(int)); 

    printf("--- Дослідження сегментів пам'яті ---\n");
    
    
    printf("Текстовий сегмент (код main):        %p\n", (void*)main);
    

    printf("Сегмент Даних (ініціалізована):      %p\n", (void*)&global_init_var);
    printf("Сегмент BSS (неініціалізована):      %p\n", (void*)&global_uninit_var);
    

    printf("Купа (динамічна пам'ять):            %p\n", (void*)heap_ptr);
    
    printf("\n--- Дослідження Стека ---\n");

    printf("Початкова вершина стека:             %p\n", (void*)&local_var);
    

    grow_stack();

    free(heap_ptr);
    return 0;
}
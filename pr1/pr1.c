#include <stdio.h>
#include <stdlib.h>

#define MIN_SIZE 1
#define MAX_SIZE 100

void printMemoryState(int *arr, int size, const char *operation)
{
    printf("\n[Memory operation: %s]\n", operation);
    printf("Array address: %p\n", arr);
    printf("Array size: %d elements\n", size);
    printf("Allocated memory: %lu bytes\n\n", size * sizeof(int));
}

void fillArray(int *arr, int size, int value)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = value;
    }
}

void printArray(int *arr, int size)
{
    printf("Array: ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    int size;
    int value;
    int *array = NULL;

    printf("Enter array size (%d - %d): ", MIN_SIZE, MAX_SIZE);
    scanf("%d", &size);

    if (size < MIN_SIZE || size > MAX_SIZE)
    {
        printf("Invalid size!\n");
        return 1;
    }

    printf("Enter number to fill array: ");
    scanf("%d", &value);

    array = (int *)malloc(size * sizeof(int));

    if (array == NULL)
    {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printMemoryState(array, size, "malloc");

    fillArray(array, size, value);
    printArray(array, size);

    int newSize;
    printf("\nEnter new array size (%d - %d): ", MIN_SIZE, MAX_SIZE);
    scanf("%d", &newSize);

    if (newSize < MIN_SIZE || newSize > MAX_SIZE)
    {
        printf("Invalid size!\n");
        free(array);
        return 1;
    }

    int *temp = realloc(array, newSize * sizeof(int));

    if (temp == NULL)
    {
        printf("Reallocation failed!\n");
        free(array);
        return 1;
    }

    array = temp;

    if (newSize > size)
    {
        for (int i = size; i < newSize; i++)
        {
            array[i] = value;
        }
    }

    size = newSize;

    printMemoryState(array, size, "realloc");
    printArray(array, size);

    free(array);
    printMemoryState(NULL, 0, "free");

    return 0;
}
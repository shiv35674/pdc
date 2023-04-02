#include<stdlib.h>
#include <stdio.h>
#include <omp.h>

#define ARRAY_SIZE 1000

void bubble_sort(int *arr, int size) {
    int i, j, temp;
    #pragma omp parallel for private(i,j,temp) shared(arr,size)
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int i;
    int arr[ARRAY_SIZE];
    double start_time, end_time;

    // Initialize the array with random values
    for (i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = rand() % 1000;
    }

    // Start the timer
    start_time = omp_get_wtime();

    // Sort the array in parallel
    bubble_sort(arr, ARRAY_SIZE);

    // End the timer
    end_time = omp_get_wtime();

    // Print the sorted array and the execution time
    printf("Sorted array: ");
    for (i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\nExecution time: %lf seconds\n", end_time - start_time);

    return 0;
}

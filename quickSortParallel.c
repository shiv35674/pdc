#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void quicksort(int *arr, int left, int right) {
    int i, j, pivot, temp;
    if (left < right) {
        pivot = left;
        i = left;
        j = right;
        while (i < j) {
            while (arr[i] <= arr[pivot] && i < right)
                i++;
            while (arr[j] > arr[pivot])
                j--;
            if (i < j) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        temp = arr[pivot];
        arr[pivot] = arr[j];
        arr[j] = temp;

        #pragma omp parallel sections
        {
            #pragma omp section
            quicksort(arr, left, j - 1);
            #pragma omp section
            quicksort(arr, j + 1, right);
        }
    }
}

int main() {
    int arr[1000];
    int i;
    double start_time, end_time;
    // Initialize the array with random values
    srand(1234);
    for (i = 0; i < 1000; i++) {
        arr[i] = rand() % 1000;
    }

    // Print the original array
    printf("Original array:\n");
    for (i = 0; i < 1000; i++) {
        printf("%d ", arr[i]);
    }
    start_time = omp_get_wtime();
    // Sort the array using quicksort
    #pragma omp parallel
    {
        #pragma omp single
        quicksort(arr, 0, 999);
    }
    end_time = omp_get_wtime();
    // Print the sorted array
    printf("\nSorted array:\n");
    for (i = 0; i < 1000; i++) {
        printf("%d ", arr[i]);
    }
    printf("\nExecution time: %lf seconds\n", end_time - start_time);
    return 0;
}

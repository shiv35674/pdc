#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void selection_sort(int *arr, int n) {
    int i, j, min_idx;

    #pragma omp parallel for shared(arr, n) private(i, j, min_idx)
    for (i = 0; i < n-1; i++) {
        min_idx = i;
        for (j = i+1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            int temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
}

int main() {
    int arr[1000];
    int i;
    double start_time,end_time;
    // Initialize array with random values
    srand(1234);
    for (i = 0; i < 1000; i++) {
        arr[i] = rand() % 1000;
    }

    // Sort the array using selection sort with OpenMP
    start_time = omp_get_wtime();
    selection_sort(arr, 1000);
    end_time = omp_get_wtime();
    // Print the sorted array
    for (i = 0; i < 1000; i++) {
        printf("%d ", arr[i]);
    }
    printf("\nExecution time: %lf seconds\n", end_time - start_time);
    printf("\n");

    return 0;
}

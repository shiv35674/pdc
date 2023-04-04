#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1000

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                merge_sort(arr, l, m);
            }
            #pragma omp section
            {
                merge_sort(arr, m + 1, r);
            }
        }
        merge(arr, l, m, r);
    }
}

int main() {
    int arr[N];
    int i;
    double start_time, end_time;
    for (i = 0; i < N; i++) {
        arr[i] = rand() % 100;
    }
    start_time = omp_get_wtime();
    merge_sort(arr, 0, N - 1);
    end_time = omp_get_wtime();
    printf("Sorted array: \n");
    for (i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }
    printf("\nExecution time: %lf seconds\n", end_time - start_time);
    printf("\n");
    return 0;
}

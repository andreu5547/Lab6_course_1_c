#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "bin_search.h"
#include "sortings.h"

#define MAS_SIZE 30

#define swap(a, b , type) type c = a; \
                          a = b;      \
                          b = c;

void rand_arr(int *arr, int len) {
    for (int i = 0; i < len; ++i) {
        arr[i] = rand() % 100;
    }
}

void print_arr(int *arr, int len) {
    for (int i = 0; i < len; ++i) {
        printf("%d ", arr[i]);
    }
    putchar('\n');
}

int main() {
    srand(time(NULL));

    // NUM 1
    puts("Num 1, swap");
    int a = 1, b = 2;

    printf("a:%d b:%d\n", a, b);
    swap(a, b, int);
    printf("a:%d b:%d\n", a, b);

    // NUM 2
    puts("\nNum 2, bin_search()");
    int *arr = malloc(sizeof(int) * MAS_SIZE);
    for (int i = 0; i < MAS_SIZE; ++i) {
        arr[i] = i;
    }
    printf("Binary search: %d\n", bin_search(arr, MAS_SIZE, 10));
    printf("Binary search rec: %d\n", bin_search_rec(arr, 0, MAS_SIZE, 10));

    // NUM 3
    puts("\nNum 3, quick sort");
    rand_arr(arr, MAS_SIZE);
    print_arr(arr, MAS_SIZE);
    quickSortHoara(arr, 0, MAS_SIZE - 1);
    print_arr(arr, MAS_SIZE);

    puts("quick sort loop");
    rand_arr(arr, MAS_SIZE);
    print_arr(arr, MAS_SIZE);
    quickSortHoara_loop(arr, 0, MAS_SIZE - 1);
    print_arr(arr, MAS_SIZE);

    // NUM 4
    puts("\nNum 4\n");
    puts("Merge sort");
    rand_arr(arr, MAS_SIZE);
    print_arr(arr, MAS_SIZE);
    mergeSort(arr, 0, MAS_SIZE - 1);
    print_arr(arr, MAS_SIZE);

    puts("Radix sort");
    rand_arr(arr, MAS_SIZE);
    print_arr(arr, MAS_SIZE);
    radixSort(arr, 0, MAS_SIZE);
    print_arr(arr, MAS_SIZE);

    puts("ShellSort sort");
    rand_arr(arr, MAS_SIZE);
    print_arr(arr, MAS_SIZE);
    ShellSort(arr, MAS_SIZE);
    print_arr(arr, MAS_SIZE);

    free(arr);
    return 0;
}

/*
 *      Sorting and finding the median
 *
 *      See: https://en.wikipedia.org/wiki/Bubble_sort and
 *           https://en.wikipedia.org/wiki/Insertion_sort
 */
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<memory.h>

#define SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

// Test macros
#define CHECK_IF_EQUALS(v1, v2) printf((v1) == (v2) ? "ok\n" : "not ok\n")

bool is_sorted(const int *arr, int size);

void bubble_sort(int *arr, int size);

void insertion_sort(int *arr, int size);

double median(const int *arr, int size);

void print_arr(const int *arr, int size);


int main(void) {
    int arr[] = {4, 5, 7, 6, 2, 8, 9, 4, 5, 3, 4, 1, 2, 3, 9, 8};
    CHECK_IF_EQUALS(is_sorted(arr, SIZE(arr)), false);

    bubble_sort(arr, SIZE(arr));
    print_arr(arr, SIZE(arr));
    CHECK_IF_EQUALS(is_sorted(arr, SIZE(arr)), true);

    int arr2[] = {1, 3, 6, 5, 7, 2, 9, 7, 8, 4, 4, 5, 3, 6, 6};
    CHECK_IF_EQUALS(is_sorted(arr2, SIZE(arr2)), false);
    insertion_sort(arr2, SIZE(arr2));
    CHECK_IF_EQUALS(is_sorted(arr2, SIZE(arr2)), true);
    print_arr(arr2, SIZE(arr2));

    // Both arrays sorted!
    printf("Size of arr is %ld median is %f\n", SIZE(arr), median(arr, SIZE(arr)));
    printf("Size of arr2 is %ld median is %f\n", SIZE(arr2), median(arr2, SIZE(arr2)));

    return 0;
}

bool is_sorted(const int *arr, int size) {
    // TODO
    return 0;
}


// Assumes sorted array
double median(const int *arr, int size) {
   // TODO
}

void bubble_sort(int *arr, int size) {
    // TODO
}

void insertion_sort(int *arr, int size) {
   // TODO
}


// ----------- Helper method -----------------

void print_arr(const int *arr, int size) {
    printf("[");
    for (int i = 0; i < size - 1; i++) {
        printf("%d, ", arr[i]);
    }
    printf("%d]\n", arr[size - 1]);
}
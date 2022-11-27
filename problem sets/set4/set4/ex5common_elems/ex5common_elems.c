/*
 *   Get common elements for all rows in matrix
 *   with positive integer elements
 */
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<memory.h>

#define ROWS 4
#define COLS 4

#define SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

// Test macros
#define CHECK_IF_EQUALS(v1, v2) printf((v1) == (v2) ? "ok\n" : "not ok\n")
#define CHECK_IF_ARR_EQUALS(v1, v2) printf( memcmp(v1, v2, sizeof(v1)) == 0 ? "ok\n" : "not ok\n")

// TODO Declarations of helper methods

void get_common_row_elems(int n_rows, int n_cols, const int matrix[][n_cols], int *common);


int main(void) {

    int m1[ROWS][COLS] = {
            {7, 1, 3, 6},
            {6, 2, 7, 1},
            {8, 9, 1, 3},
            {5, 6, 9, 1},
    };
    int m2[ROWS][COLS] = {
            {7, 1, 3, 9},
            {6, 9, 7, 1},
            {7, 9, 1, 3},
            {5, 7, 9, 1},
    };

    // TODO Add tests for helper methods


    int expected[] = {1, 0, 0, 0};  // Padded with 0's
    int result[COLS];
    get_common_row_elems(ROWS, COLS, m1, result);
    CHECK_IF_ARR_EQUALS(result, expected);


    int expected2[] = {7, 1, 9, 0};  // Padded with 0's
    int result2[COLS];
    get_common_row_elems(ROWS, COLS, m2, result2);
    CHECK_IF_ARR_EQUALS(result2, expected2);


    return 0;
}


// Get all elements present on all rows
void get_common_row_elems(int n_rows, int n_cols, const int matrix[][n_cols], int *common) {
    // TODO
}


// ----------- Helper method -----------------

void print_arr(const int arr[], int size) {
    printf("[");
    for (int i = 0; i < size - 1; i++) {
        printf("%d, ", arr[i]);
    }
    printf("%d]\n", arr[size - 1]);
}
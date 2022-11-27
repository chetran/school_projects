/*
 *      Pointers and Matrices
 */
#include<stdio.h>
#include<memory.h>

#define ROWS 2
#define COLS 3

// Our standard style calling function with matrix parameter
int sum1(int n_rows, int n_cols, const int matrix[][n_cols]);

// Also possible, but can't use 2 indices in function
int sum2(int n_rows, int n_cols, const int *matrix);  // Single pointer!

// Helper
void print_matrix(int n_rows, int n_cols, const int matrix[][n_cols]);

// Helper
void print_arr(const int arr[], int size);


int main(void) {

    int mtr1[ROWS][COLS] = {   // The matrix
            {1, 1, 0},
            {0, 0, 1},
    };
    printf("%d\n", sum1(ROWS, COLS, mtr1));
    printf("%d\n", sum2(ROWS, COLS, (const int *) mtr1));  // Cast away warning
}



// ------------- Functions -----------------------

// Good way to do it ...
int sum1(int n_rows, int n_cols, const int matrix[][n_cols]) {
    int s = 0;
    for (int r = 0; r < n_rows; r++) {
        for (int c = 0; c < n_cols; c++) {
            s = s + matrix[r][c];
        }
    }
    return s;
}

// ... but this also possible. NOTE: Pointer variable,
// so matrix[row][col] NOT possible. Can't use two indices on pointer.
int sum2(int n_rows, int n_cols, const int *matrix) {
    int s = 0;
    for (int i = 0; i < n_rows * n_cols; i++) {
        s += *matrix++;   // Calculate right side first!
    }
    return s;
}


void print_matrix(int n_rows, int n_cols, const int matrix[][n_cols]) {
    for (int r = 0; r < n_rows; r++) {
        for (int c = 0; c < n_cols; c++) {
            printf("%d ", matrix[r][c]);
        }
        printf("\n");
    }
}

void print_arr(const int arr[], int size) {
    printf("[");
    for (int i = 0; i < size - 1; i++) {
        printf("%d, ", arr[i]);
    }
    printf("%d]\n", arr[size - 1]);
}


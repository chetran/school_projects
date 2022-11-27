/*
 *      Pointers and Matrices
 */
#include<stdio.h>
#include<memory.h>


#define ROWS 2
#define COLS 3

// Helper function
void print_arr(const int arr[], int size);

// Helper function
void print_matrix(int n_rows, int n_cols, const int matrix[][n_cols]);


int main(void) {
    int mtr[ROWS][COLS] = {   // The matrix
            {1, 2, 3},        // m[0]
            {4, 5, 6},        // m[1]
    };

    // ----- Pointer to full matrix ------------

    int (*ptr1)[COLS] = mtr;        // Strange type, a single pointer to an array of size COLS
    ptr1[0][1] = 9;                 // Ok, know col size, can use index
    print_matrix(ROWS, COLS, ptr1);


    int *ptr2 = (int *) mtr;         // Cast away warning but no problem to run
    //ptr2[1][2] = 9;                // NO! Only one index for a int* pointer!
    ptr2[1 * COLS + 2] = 9;          // Calculate address by hand (avoid)
    print_matrix(ROWS, COLS, ptr2);  // To remove warning cast: (int (*)[COLS])

    // --------- Definitions -----------------------

    int mtr1[ROWS][COLS] = {   // The matrix
            {1, 1, 0},
            {0, 0, 1},
    };
    /*
      Definitions like arrays
   */
    printf("%d\n", mtr1 == &mtr1[0]);        // True

    printf("%d\n", mtr1[1] == *(mtr1 + 1));  // True (mtr1 is an address!)

    int *ptr = mtr1[1];   // Will get array starting at offset 1
                          // Array converted to address to first elem (as before)

    // -------- Working with rows ---------------------

    int *row1 = mtr[1];              // No need to cast
    row1[0] = 9;                     // Indexing on row 1, just need column index
    print_arr(row1, COLS);
    print_matrix(ROWS, COLS, mtr);

    int *row0 = mtr[0];

    int *rows[ROWS];              // An array of int pointers to int
    rows[0] = row0;
    rows[1] = row1;
    for (int i = 0; i < ROWS; i++) {
        print_arr(rows[i], COLS);
    }
    // Or like this 
    rows[0] = mtr[0];
    rows[1] = mtr[1];

    // Or like this
    for (int j = 0; j < ROWS; j++) {
        rows[j] = mtr[j];
    }
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

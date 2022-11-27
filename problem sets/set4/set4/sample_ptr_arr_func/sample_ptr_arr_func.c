/*
 *      Arrays or Pointers as function parameters
 */
#include<stdio.h>

// Sum array (array should not change so make it const)
int sum(const int arr[], int size);

// Sum array, using a pointer parameter
int sum_p(const int *ptr, int size);

// Sum array, using a pointer parameter (sum in another way)
int sum_p_2(int *ptr, int size);

// Increment all elements in array original changed
void inc(int *arr, int size);

// Increment all elements in array and return (changed) original
int *inc1(int *arr, int size);

// Increment all elements in array original unchanged
void inc2(int *dest, const int *arr, int size);

// Prints an array
void print_arr(const int *arr, int size);


int main(void) {

    int arr[] = {1, 2, 3, 4, 5};
    printf("Size of full array is: %ld\n", sizeof(arr));  // 5 * 4 = 20

    printf("%d\n", sum(arr, 5));
    printf("%d\n", sum_p(arr, 5));
    printf("%d\n", sum_p_2(arr, 5));

    int size = 5;
    inc(arr, size);
    print_arr(arr, size);

    int *ptr = inc1(arr, size);
    print_arr(ptr, size);

    int dest[size];
    inc2(dest, arr, size);
    print_arr(dest, size);

    //int arr2[SIZE];         // No, get an address as result
    //arr2 = inc(arr, SIZE);

    return 0;
}


int sum(const int arr[], int size) {
    printf("%ld\n", sizeof(arr));  // 8, arr single pointer variable
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum = sum + arr[i];
    }
    return sum;
}

int sum_p(const int *ptr, int size) {   // Same as sum but using explicit pointer variable
    printf("%ld\n", sizeof(ptr));  // 8, arr single pointer variable
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum = sum + ptr[i];
    }
    return sum;
}

int sum_p_2(int *ptr, int size) { // Same as sum_p but advanced C idiom
    int sum = 0;
    int *i = ptr + size;
    while (ptr < i) {   // Pointer arithmetic
        sum = sum + *ptr++;   // Get value (*), step pointer (++), assign value (+=)
    }
    return sum;
}

// ---------- Three approaches to the same function -------------------

void inc(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i]++;
    }
}

int *inc1(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i]++;
    }
    return arr;
}

void inc2(int *dest, const int *arr, int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = arr[i] + 1;
    }
}

// ----------- Helper method -----------------

void print_arr(const int *arr, int size) {
    printf("[");
    for (int i = 0; i < size - 1; i++) {
        printf("%d, ", arr[i]);
    }
    printf("%d]\n", arr[size - 1]);
}
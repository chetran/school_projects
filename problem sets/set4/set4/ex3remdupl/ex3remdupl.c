/*
 *   Remove duplicates from sorted array
 */
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<memory.h>

#define SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

// Test macros
#define CHECK_IF_EQUALS(v1, v2) printf((v1) == (v2) ? "ok\n" : "not ok\n")
#define CHECK_IF_ARR_EQUALS(v1, v2) printf( memcmp(v1, v2, sizeof(v1)) == 0 ? "ok\n" : "not ok\n")

// Inputs src (with duplicates) and get dest (without duplicates)
void remove_dupl(int *dest, const int *src, int size);


int main(void) {

    int arr[] = {1, 1, 2, 2, 2, 2, 3};

    int result[SIZE(arr)];
    remove_dupl(result, arr, SIZE(arr));
    int expected[] = {1, 2, 3, 0, 0, 0, 0};
    CHECK_IF_ARR_EQUALS(expected, result);
    
    int arr2[] = {3, 3, 3, 5, 5, 5, 5, 5, 7, 7};

    int result2[SIZE(arr2)];
    remove_dupl(result2, arr2, SIZE(arr2));
    int expected2[] = {3, 5, 7, 0, 0, 0, 0, 0, 0, 0};
    CHECK_IF_ARR_EQUALS(expected2, result2);

    return 0;

}


void remove_dupl(int *dest, const int *src, int size) {
   // TODO 
}

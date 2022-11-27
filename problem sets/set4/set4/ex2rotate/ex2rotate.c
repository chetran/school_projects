/*
 *  Rotating elements in array using different approaches.
 */
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<memory.h>

#define SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

// Test macro
#define CHECK_IF_ARR_EQUALS(v1, v2) printf( memcmp(v1, v2, sizeof(v1)) == 0 ? "ok\n" : "not ok\n")

// Rotate array elements "steps" position to the right in a circular
// fashion. Changing original
void rotate(int *arr, int size, int steps);

// Rotate array in same manner and return rotated (original changed and returned)
int *rotate1(int *arr, int size, int steps);

// Rotate in same manner original (src) unchanged. dest array returned.
void rotate2(int *dest, const int *src, int size, int steps);


int main(void) {

    int arr[] = {1, 2, 3, 4, 5};
    rotate(arr, SIZE(arr), 2);
    int expected[] = {4, 5, 1, 2, 3};
    CHECK_IF_ARR_EQUALS(expected, arr);

    int arr1[] = {1, 2, 3, 4, 5};
    int *r = rotate1(rotate1(arr1, SIZE(arr1), 2), SIZE(arr1), 2);
    int expected1[] = {2, 3, 4, 5, 1};
    CHECK_IF_ARR_EQUALS(expected1, r);

    int arr2[] = {1, 2, 3, 4, 5};
    int dest[5];
    rotate2(dest, arr2, SIZE(arr2), 2);
    int expected2[] = {4, 5, 1, 2, 3};
    CHECK_IF_ARR_EQUALS(expected2, dest);

    return 0;
}


// Param arr modified
void rotate(int *arr, int size, int steps) {
   // TODO 
   for (int i = 0; i < size; i++)
   {
      int index = i + steps;
      if (index > size)
      {
         index = i - steps;
      }
      arr[index] = arr[i];
   }
   for (int i = 0; i < size; i++)
   {
      printf("%i\n", arr[i]);
   }
}

// Param arr modified return incoming array
int *rotate1(int *arr, int size, int steps) {
   // TODO 
}

// Param src NOT modified
void rotate2(int *dest, const int *src, int size, int steps) {
   // TODO 
}



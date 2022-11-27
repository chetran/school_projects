/*
 *      Pointers and Arrays
 *
 *      Fundamental equalities:
 *
 *      arr == &arr[0]
 *      arr[n] == *(arr + n)
 */

#include<stdio.h>


int main(void) {

    int arr[] = {1, 2, 3, 4, 5};

    /*
     * Name of array (arr) converted to &arr[0], i.e. address to first element
     * (with a few exception, notably the sizeof operator)
     */
    printf("%d\n", arr == &arr[0]);  // True

    printf("%ld\n", sizeof(arr));    // An exception. NOT the address. Print 20!

    /*
    *  Indexing defined as:
    *  a[n] == *(arr + n)
    *
    *  I.e. get variable n memory steps from base address (&arr[0]).
    *  Each step is sizeof the elements (pointer arithmetic)
    */
    printf("%d\n", arr[3] == *(arr + 3));

    /*
     * Assign array to pointer variable
     */
    int *ptr = arr;                        // NO &, arr is address to arr[0]!
    printf("%d\n", *ptr == arr[0]);        // True
    printf("%d\n", *(ptr + 1) == arr[1]);  // True
    printf("%d\n", *(ptr + 2) == arr[2]);  // True


    //ptr = arr[2];    // Bad, arr[2] not an address
    ptr = &arr[2];   // Ok!

    /*
     * Indexing on pointer ok!
     */
    printf("%d\n", ptr[0]);  // Ok
    printf("%d\n", ptr[1]);  // Ok

    /*
     *  What is const? Variables in array or pointer to array?
     */
    const int *ptr2 = ptr;    // Pointer is not const!
    //ptr2[0] = 74;            // Variables are const
    ptr2++;

    int *const ptr3 = ptr;
    ptr3[0] = 74;            // Variables are NOT const
    //ptr3++;                // Pointer is const!

    const int *const ptr4 = ptr; // Pointer and variables const
    //ptr4[0] = 74;          
    //ptr4++;               

    /*
     * Use pointer to print array (just a demo)
     */
    ptr = arr;
    while (ptr < &arr[5]) {
        printf("%d ", *ptr++); // Typical C-idiom.
    }

    return 0;
}


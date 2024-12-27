#include <stdio.h>

int main(void)
{
    // Variable declarations

    // Declaring character arrays for separate values
    char ch_arr1[] = { 'A', 'S', 'T', 'R', 'O', 'M', 'E', 'D', 'I', 'C', 'O', 'M', 'P', '\0' };
    char ch_arr2[] = { 'W', 'E', 'L', 'C', 'O', 'M', 'E', 'S', '\0' };
    char ch_arr3[] = { 'Y', 'O', 'U', '\0' };

    // Declaring character arrays for strings
    char ch_arr5[] = "TO";
    char ch_arr6[] = "REAL TIME RENDERING BATCH OF 2020-2021";
    char ch_arr_no_null[] = {'H', 'E', 'L', 'L', 'O'};
    
    // Printing sizes of all arrays
    printf("\nSizes of arrays:\n");
    printf("Size of ch_arr1: %lu bytes\n", sizeof(ch_arr1));
    printf("Size of ch_arr2: %lu bytes\n", sizeof(ch_arr2));
    printf("Size of ch_arr3: %lu bytes\n", sizeof(ch_arr3));
    printf("Size of ch_arr5: %lu bytes\n", sizeof(ch_arr5));
    printf("Size of ch_arr6: %lu bytes\n", sizeof(ch_arr6));

    printf("\n\n");
    printf("\nStrings:\n");
    // Displaying separate character arrays
    printf("ch_arr1: %s\n", ch_arr1);
    printf("ch_arr2: %s\n", ch_arr2);
    printf("ch_arr3: %s\n", ch_arr3);

    // Displaying string arrays
    printf("ch_arr5: %s\n", ch_arr5);
    printf("ch_arr6: %s\n", ch_arr6);

    printf("Size of ch_arr_no_null: %lu bytes\n", sizeof(ch_arr_no_null));
    printf("ch_arr_no_null: %s\n", ch_arr_no_null);

    return 0;
}

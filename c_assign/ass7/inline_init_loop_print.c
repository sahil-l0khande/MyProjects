#include <stdio.h>

int main(void)
{
    // variable declarations
    int iarr[] = {9, 30, 6, 12, 98, 20, 23, 2, 45};
    int int_siz, iarr_size, iarr_num_elements;

    float farr[] = {1.2f, 2.3f, 3.4f, 4.5f, 4.5f, 5.6f, 6.7f, 7.8f, 8.9f};
    int float_siz, farr_size, farr_num_elements;

    char carr[] = { 'A', 's', 't', 'r', 'o', 'm', 'e', 'd', 'i', 'c', 'o', 'm', 'p', '\0' };
    int char_siz, carr_size, carr_num_elements;

    // calculate sizes and number of elements
    int_siz = sizeof(int);
    iarr_size = sizeof(iarr);
    iarr_num_elements = iarr_size / int_siz;

    float_siz = sizeof(float);
    farr_size = sizeof(farr);
    farr_num_elements = farr_size / float_siz;

    char_siz = sizeof(char);
    carr_size = sizeof(carr);
    carr_num_elements = carr_size / char_siz;

    // print elements of iarr
    printf("\nIn-line initialization and piece-meal display of elements of array 'iarr[]':\n\n");
    for (int i = 0; i < iarr_num_elements; i++) {
        printf("iarr[%d] (element %d) = %d\n", i, (i + 1), iarr[i]);
    }

    printf("\nSize of data type 'int'             = %d bytes\n", int_siz);
    printf("Number of elements in int array iarr  = %d elements\n", iarr_num_elements);
    printf("Size of array iarr (%d elements * %d bytes) = %d bytes\n\n", iarr_num_elements, int_siz, iarr_size);

    // print elements of farr
    printf("\nIn-line initialization and piece-meal display of elements of array 'farr[]':\n\n");
    for (int i = 0; i < farr_num_elements; i++) {
        printf("farr[%d] (element %d) = %.2f\n", i, (i + 1), farr[i]);
    }

    printf("\nSize of data type 'float'             = %d bytes\n", float_siz);
    printf("Number of elements in float array farr  = %d elements\n", farr_num_elements);
    printf("Size of array farr (%d elements * %d bytes) = %d bytes\n\n", farr_num_elements, float_siz, farr_size);

    // print elements of carr
    printf("\nIn-line initialization and piece-meal display of elements of array 'carr[]':\n\n");
    for (int i = 0; i < carr_num_elements; i++) {
        printf("carr[%d] (element %d) = %c\n", i, (i + 1), carr[i]);
    }

    printf("\nSize of data type 'char'             = %d bytes\n", char_siz);
    printf("Number of elements in char array carr  = %d elements\n", carr_num_elements);
    printf("Size of array carr (%d elements * %d bytes) = %d bytes\n\n", carr_num_elements, char_siz, carr_size);

    return 0;
}


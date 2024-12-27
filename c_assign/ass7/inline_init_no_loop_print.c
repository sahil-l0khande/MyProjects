#include <stdio.h>

int main(void)
{
    // variable declarations
    int iarr[] = {9, 30, 6, 12, 98, 20, 23, 2, 45};
    int int_siz;
    int iarr_size;
    int iarr_num_elements;

    float farr[] = {1.2f, 2.3f, 3.4f, 4.5f, 4.5f, 5.6f, 6.7f, 7.8f, 8.9f};
    int float_siz;
    int farr_size;
    int farr_num_elements;

    char carr[] = { 'A', 's', 't', 'r', 'o', 'm', 'e', 'd', 'i', 'c', 'o', 'm', '\0' };

    int char_size;
    int carr_size;
    int carr_num_elements;

    // code

    // iarrr

    printf("\n\n");

    printf("In-line  initialization and piece-meal display of elements of array 'iarr[]' : \n\n");

    printf("iarr[0] (1st element) = %d\n", iarr[0]);
    printf("iarr[1] (2nd element) = %d\n", iarr[1]);
    printf("iarr[2] (3rd element) = %d\n", iarr[2]);
    printf("iarr[3] (4th element) = %d\n", iarr[3]);
    printf("iarr[4] (5th element) = %d\n", iarr[4]);
    printf("iarr[5] (6th element) = %d\n", iarr[5]);
    printf("iarr[6] (7th element) = %d\n", iarr[6]);
    printf("iarr[7] (8th element) = %d\n", iarr[7]);
    printf("iarr[8] (9th element) = %d\n", iarr[8]);
    printf("iarr[9] (10th element) = %d\n", iarr[9]);

    int_siz  = sizeof(int);
    iarr_size = sizeof(iarr);
    iarr_num_elements = iarr_size / int_siz;

    printf("Size of data type 'int'             = %d bytes\n", int_siz);
    printf("Number of elements in int array iarr  = %d elements\n", iarr_num_elements);
    printf("Size of array iarr (%d elements * %d bytes) = %d bytes\n\n", iarr_num_elements, int_siz, iarr_size);

    // farr
        printf("\n\n");

    printf("In-line  initialization and piece-meal display of elements of array 'farr[]' : \n\n");

    printf("farr[0] (1st element) = %.2f\n", farr[0]);
    printf("farr[1] (2nd element) = %.2f\n", farr[1]);
    printf("farr[2] (3rd element) = %.2f\n", farr[2]);
    printf("farr[3] (4th element) = %.2f\n", farr[3]);
    printf("farr[4] (5th element) = %.2f\n", farr[4]);
    printf("farr[5] (6th element) = %.2f\n", farr[5]);
    printf("farr[6] (7th element) = %.2f\n", farr[6]);
    printf("farr[7] (8th element) = %.2f\n", farr[7]);
    printf("farr[8] (9th element) = %.2f\n", farr[8]);
    printf("farr[9] (10th element) = %.2f\n", farr[9]);


    float_siz = sizeof(float);
    farr_size = sizeof(farr);
    farr_num_elements = farr_size / float_siz;
    printf("Size of data type 'float'             = %d bytes\n", float_siz);
    printf("Number of elements in float array farr  = %d elements\n", farr_num_elements);
    printf("Size of array farr (%d elements * %d bytes) = %d bytes\n\n", farr_num_elements, float_siz, farr_size);

    printf("carr[0] (1st element) = %c\n", carr[0]);
    printf("carr[1] (2nd element) = %c\n", carr[1]);
    printf("carr[2] (3rd element) = %c\n", carr[2]);
    printf("carr[3] (4th element) = %c\n", carr[3]);
    printf("carr[4] (5th element) = %c\n", carr[4]);
    printf("carr[5] (6th element) = %c\n", carr[5]);
    printf("carr[6] (7th element) = %c\n", carr[6]);
    printf("carr[7] (8th element) = %c\n", carr[7]);
    printf("carr[8] (9th element) = %c\n", carr[8]);
    printf("carr[9] (10th element) = %c\n", carr[9]);

    char_size = sizeof(char);
    carr_size = sizeof(carr);
    carr_num_elements = carr_size / char_size;
    printf("Size of data type 'char'             = %d bytes\n", char_size);
    printf("Number of elements in char array carr  = %d elements\n", carr_num_elements);
    printf("Size of array carr (%d elements * %d bytes) = %d bytes\n\n", carr_num_elements, char_size, carr_size);

    return (0);
}
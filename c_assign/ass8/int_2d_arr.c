#include <stdio.h>
int main(void)
{
    // variable declarations
    int i_arr[5][3] = {
        { 1, 2, 3},
        {2, 4, 6},
        {3, 6, 9},
        {4, 8, 12},
        {5, 10, 15}
    };

    int int_size;
    int i_arr_size;
    int i_arr_num_element, i_arr_num_rows, i_arr_num_columns;

    // Code
    printf("\n\n");

    int_size = sizeof(int);

    i_arr_size = sizeof(i_arr);
    printf("Size of two dimentional (2D) integer array is = %d\n\n", i_arr_size);

    i_arr_num_rows = i_arr_size / sizeof(i_arr[0]);
    printf("Number of rows in two dimentional (2D) integer array is = %d\n\n", i_arr_num_rows);

    i_arr_num_columns =  sizeof(i_arr[0]) / int_size;
    printf("Number of columns in two dimentional (2D) integer array is = %d\n\n", i_arr_num_columns);
    
    i_arr_num_element =  i_arr_num_rows * i_arr_num_columns;
    printf("Number of elements in two dimentional (2D) integer array is = %d\n\n", i_arr_num_element);
    
    printf("\n\n");
    printf("elements in the 2d array : \n\n");

    // Row 1
    printf("******* ROW 1 *********\n");
    printf("i_arr[0][0] = %d\n", i_arr[0][0]);
    printf("i_arr[0][1] = %d\n", i_arr[0][1]);
    printf("i_arr[0][2] = %d\n", i_arr[0][2]);

    printf("\n\n");
    // Row 2
    printf("******* ROW 2 *********\n");
    printf("i_arr[1][0] = %d\n", i_arr[1][0]);
    printf("i_arr[1][1] = %d\n", i_arr[1][1]);
    printf("i_arr[1][2] = %d\n", i_arr[1][2]);

    printf("\n\n");
    // Row 3
    printf("******* ROW 3 *********\n");
    printf("i_arr[2][0] = %d\n", i_arr[2][0]);
    printf("i_arr[2][1] = %d\n", i_arr[2][1]);
    printf("i_arr[2][2] = %d\n", i_arr[2][2]);

    printf("\n\n");
    // Row 4
    printf("******* ROW 4 *********\n");
    printf("i_arr[3][0] = %d\n", i_arr[3][0]);
    printf("i_arr[3][1] = %d\n", i_arr[3][1]);
    printf("i_arr[3][2] = %d\n", i_arr[3][2]);

    printf("\n\n");
    // Row 5
    printf("******* ROW 5 *********\n");
    printf("i_arr[4][0] = %d\n", i_arr[4][0]);
    printf("i_arr[4][1] = %d\n", i_arr[4][1]);
    printf("i_arr[4][2] = %d\n", i_arr[4][2]);

    printf("\n\n");

    return (0);
}
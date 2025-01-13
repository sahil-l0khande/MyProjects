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
    int i, j;
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

    for (i = 0; i < i_arr_num_rows; i++)
    {
        printf("******* ROW %d ******\n", (i + 1));
        for (j = 0; j < i_arr_num_columns; j++)
        {
            printf("i_arr[%d][%d] = %d\n", i, j, i_arr[i][j]);
        }
        printf("\n\n");
    }

    return (0);
}
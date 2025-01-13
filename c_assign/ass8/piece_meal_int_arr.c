#include <stdio.h>
int main(void)
{
    // variable declarations
    int i_arr[3][5];

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

    // ************ PIECE-MEAL ASSIGNMENT ********
    // ************ ROW 1 *********
    i_arr[0][0] = 21;
    i_arr[0][1] = 42;
    i_arr[0][2] = 63;
    i_arr[0][3] = 84;
    i_arr[0][4] = 105;
    
    // ******* ROW 2 ******
    i_arr[1][0] = 22;
    i_arr[1][1] = 44;
    i_arr[1][2] = 66;
    i_arr[1][3] = 88;
    i_arr[1][4] = 110;
    
    
    // ******* ROW 3 ******
    i_arr[2][0] = 23;
    i_arr[2][1] = 46;
    i_arr[2][2] = 69;
    i_arr[2][3] = 92;
    i_arr[2][4] = 115;

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
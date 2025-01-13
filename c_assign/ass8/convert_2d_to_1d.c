#include <stdio.h>

#define NUM_ROWS 5
#define NUM_COLUMNS 3

int main(void)
{
    // Varaible declarations
    int i_arr_2d[NUM_ROWS][NUM_COLUMNS];
    int i_arr[NUM_ROWS * NUM_COLUMNS];

    int i, j;
    int num;

    // Code 
    printf("Enter element of your choice to fill up the integer 2d array : \n\n");

    for (i = 0; i < NUM_ROWS; i++)
    {
        printf("For ROW NUMBER %d : \n", (i + 1));
        for (j = 0; j < NUM_COLUMNS; j++)
        {
            printf("Enter element number %d : \n", (j + 1));
            scanf("%d", &num);
            i_arr_2d[i][j] = num;
        }
        printf("\n\n");
    }

    // *** DISPLAY OF 2D ARRAY ***  
    printf("Two-dimentional (2d) array of integer : \n\n");

    for (i = 0; i < NUM_ROWS; i++)
    {
        printf("For ROW NUMBER %d : \n", (i + 1));
        for (j = 0; j < NUM_COLUMNS; j++)
        {
            printf("i_arr_2d[%d][%d] = %d \n", i, j, i_arr_2d[i][j]);
        }
        printf("\n\n");
    }

    // *** CONVERT 2d to 1d INT ARRAY *** 
    for (i = 0; i < NUM_ROWS; i++)
    {
        printf("For ROW NUMBER %d : \n", (i + 1));
        for (j = 0; j < NUM_COLUMNS; j++)
        {
            i_arr[(i * NUM_COLUMNS) + j] = i_arr_2d[i][j];
        }
        printf("\n\n");
    }

    // *** PRINTING 1D ARRAY ***
    printf("\n\n");
    printf("One-dimentional ( 1D) array of integer : \n\n");
    for (i = 0; i < (NUM_ROWS * NUM_COLUMNS); i++)
    {

            printf("i_arr_1d[%d] = %d \n", i, i_arr[i]);

    }
    
    printf("\n\n");
    
    return (0);
}
#include <stdio.h>

#define MAX_STRING_LENGTH 512

int main(void)
{
    // Function prototype 
    void mystrcpy(char[], char[]);
    // variable declarations
    char str_arr[5][10];

    int char_size;
    int str_arr_size;
    int str_arr_num_element, str_arr_num_rows, str_arr_num_columns;
    int str_actual_num_chars = 0;
    int i, j;
    // Code
    printf("\n\n");

    char_size = sizeof(char);

    str_arr_size = sizeof(str_arr);
    printf("Size of two dimentional (2D) integer array is = %d\n\n", str_arr_size);

    str_arr_num_rows = str_arr_size / sizeof(str_arr[0]);
    printf("Number of rows in two dimentional (2D) integer array is = %d\n\n", str_arr_num_rows);

    str_arr_num_columns =  sizeof(str_arr[0]) / char_size;
    printf("Number of columns in two dimentional (2D) integer array is = %d\n\n", str_arr_num_columns);
    
    str_arr_num_element =  str_arr_num_rows * str_arr_num_columns;
    printf("Number of elements in two dimentional (2D) integer array is = %d\n\n", str_arr_num_element);
    
    // *** PIECE-MEAL ASSIGNMENT ***
    // ****** ROW 1 / STRING 1
    str_arr[0][0] = 'M';
    str_arr[0][1] = 'y';
    str_arr[0][2] = '\0';
    
    str_arr[1][0] = 'N';
    str_arr[1][1] = 'a';
    str_arr[1][2] = 'm';
    str_arr[1][3] = 'e';
    str_arr[1][4] = '\0';
    
    str_arr[2][0] = 'I';
    str_arr[2][1] = 's';
    str_arr[2][2] = '\0';
    
    str_arr[3][0] = 'S';
    str_arr[3][1] = 'a';
    str_arr[3][2] = 'h';
    str_arr[3][3] = 'i';
    str_arr[3][4] = 'l';
    str_arr[3][5] = '\0';

    str_arr[4][0] = 'L';
    str_arr[4][1] = 'o';
    str_arr[4][2] = 'k';
    str_arr[4][3] = 'h';
    str_arr[4][4] = 'a';
    str_arr[4][5] = 'n';
    str_arr[4][6] = 'd';
    str_arr[4][7] = 'e';
    str_arr[4][8] = '\0';
    


    printf("\n\n");

    printf("Strings in the 2D array : \n\n");

    for (i = 0; i < str_arr_num_rows; i++)
    {
        printf("%s ", str_arr[i]);
    }

    printf("\n\n");

    return (0);
}

int mystrlen(char str[])
{
	// varaible declarations
	
	int j;
	int string_len = 0;

	// code 
	
	for (j = 0; j < MAX_STRING_LENGTH; j++)
	{
		if (str[j] == '\0')
			break;
		else
			string_len++;
	}

	return (string_len);
}
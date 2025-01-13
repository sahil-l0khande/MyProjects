#include <stdio.h>

#define MAX_STRING_LENGTH 512

int main(void)
{
    // Function prototype 
    int mystrlen(char[]);
    // variable declarations
    char str_arr[10][15] = {
        "Hello",
        "Welcome",
        "To",
        "Real",
        "Time",
        "Rendering",
        "Batch",
        "(2020-21)",
        "Of",
        "ASTROMEDICOMP."
    };

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
    
    for (i = 0; i < str_arr_num_rows; i++)
    {
        str_actual_num_chars  = str_actual_num_chars + mystrlen(str_arr[i]);
    }

    printf("Actual number of element (characters) in two dimentional (2D) character array (string array) is = %d\n\n", str_actual_num_chars);
    printf("\n\n");

    printf("Strings int the 2D array : \n\n");

    printf("%s ", str_arr[0]);
    printf("%s ", str_arr[1]);
    printf("%s ", str_arr[2]);
    printf("%s ", str_arr[3]);
    printf("%s ", str_arr[4]);
    printf("%s ", str_arr[5]);
    printf("%s ", str_arr[6]);
    printf("%s ", str_arr[7]);
    printf("%s ", str_arr[8]);
    printf("%s \n\n", str_arr[9]);

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
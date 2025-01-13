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
    
    mystrcpy(str_arr[0], "My");
    mystrcpy(str_arr[1], "Name");
    mystrcpy(str_arr[2], "Is");
    mystrcpy(str_arr[3], "Sahil");
    mystrcpy(str_arr[4], "Lokhande");


    printf("\n\n");

    printf("Strings in the 2D array : \n\n");

    for (i = 0; i < str_arr_num_rows; i++)
    {
        printf("%s ", str_arr[i]);
    }

    printf("\n\n");

    return (0);
}

void mystrcpy(char* dest, char src[])
{
	// function prototype
	
	int mystrlen(char[]);

	int str_len = 0;
	int j;

	// code
	
	str_len = mystrlen(src);
	for(j = 0; j < str_len; j++)
		dest[j] = src[j];

	dest[j] = '\0';
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
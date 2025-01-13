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

    int i_strlen[10];
    int str_arr_size;
    int str_arr_num_rows, str_arr_num_columns;
    int str_actual_num_chars = 0;
    int i, j;
    // Code
    printf("\n\n");


    str_arr_size = sizeof(str_arr);
    str_arr_num_rows = str_arr_size / sizeof(str_arr[0]);

    // Storing in length of all the strings
    for (i = 0; i < str_arr_num_rows; i++)
        i_strlen[i] = mystrlen(str_arr[i]);

    printf("\n\n");
    printf("The entire string array : \n\n");
    for (i = 0; i < str_arr_num_rows; i++)
    {
        printf("%s ", str_arr[i]);
        //str_actual_num_chars  = str_actual_num_chars + mystrlen(str_arr[i]);
    }

    printf("\n\n");

    printf("Strings in the 2D array : \n\n");

    for (i = 0; i < str_arr_num_rows; i++)
    {
        printf("String number %d => %s\n\n", (i + 1), str_arr[i]);
        for (j = 0; j < i_strlen[i]; j++)
        {
            printf("Character %d = %c \n", (j + 1), str_arr[i][j]);
        }
        printf("\n\n");
    }


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
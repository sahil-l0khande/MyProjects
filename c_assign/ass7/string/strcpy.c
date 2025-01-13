#include <stdio.h>
#include <string.h>

#define MAX_STRING_LENGTH 512

int main(void)
{
	// variable declarations
	char *chArray, ch_arr_copy[MAX_STRING_LENGTH];
	int str_length = 0;
	int len = MAX_STRING_LENGTH;
	// code
	
	printf("\n\n");
	printf("Enter a string : \n\n");
	getline(&chArray, &len, stdin);

	strcpy(ch_arr_copy, chArray);
	printf("\n\n");
        printf("String entered by you is : \n\n");
	printf("%s\n", chArray);

	printf("\n\n");
        printf("Copied string is : %s\n", ch_arr_copy);

	return (0);
}



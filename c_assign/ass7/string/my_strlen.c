#include <stdio.h>
#include <string.h>

#define MAX_STRING_LENGTH 512

int main(void)
{
	// variable declarations
	char* chArray;
	int str_length = 0;
	int len = MAX_STRING_LENGTH;
	// code
	
	printf("\n\n");
	printf("Enter a string : \n\n");
	getline(&chArray, &len, stdin);

	printf("\n\n");
        printf("String entered by you is : \n\n");
	printf("%s\n", chArray);

	printf("\n\n");
	str_length = strlen(chArray);
        printf("Length of a String = %d charactes !!!: \n\n", str_length);

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

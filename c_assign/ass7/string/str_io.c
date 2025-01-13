#include <stdio.h>

#define MAX_STRING_LENGTH 512

int main(void)
{
	// variable declarations
	char* chArray;

	int len = MAX_STRING_LENGTH;
	// code
	
	printf("\n\n");
	printf("Enter a string : \n\n");
	getline(&chArray, &len, stdin);

	printf("\n\n");
        printf("String entered by you is : \n\n");
	printf("%s\n", chArray);

	return (0);
}



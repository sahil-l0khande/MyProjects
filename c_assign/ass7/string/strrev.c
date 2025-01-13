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
        printf("The reversed string = %s charactes !!!: \n\n", strrev(chArray));

	return (0);
}



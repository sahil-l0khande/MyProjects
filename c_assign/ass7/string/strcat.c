#include <stdio.h>
#include <string.h>

#define MAX_STRING_LENGTH 512

int main(void)
{
	// variable declarations
	char chArray[MAX_STRING_LENGTH], ch_arr_cat[MAX_STRING_LENGTH];
	int str_length = 0;
	int len = 6;
	// code
	
	printf("\n\n");
	printf("Enter a string : \n\n");
	scanf("%s", chArray);

	printf("Enter 2nd string\n\n");
	scanf("%s", ch_arr_cat);

	strcat(chArray,ch_arr_cat);
	
	printf("\n\n");
        printf("String entered by you is : \n\n");
	printf("%s\n", ch_arr_cat);

	printf("\n\n");
        printf("Copied string is : %s\n", chArray);

	return (0);
}



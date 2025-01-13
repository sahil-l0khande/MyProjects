#include <stdio.h>
#include <string.h>

#define MAX_STRING_LENGTH 512

int main(void)
{
	// variable declarations
	char chArray[MAX_STRING_LENGTH], ch_arr_copy[MAX_STRING_LENGTH];
	int str_length = 0;
	int len = MAX_STRING_LENGTH;
	// code
	
	printf("\n\n");
	printf("Enter a string : \n\n");
	fgets(chArray, 5, stdin);

	mystrcpy(ch_arr_copy, chArray);
	printf("\n\n");
        printf("String entered by you is : \n\n");
	printf("%s\n", chArray);

	printf("\n\n");
        printf("Copied string is : %s\n", ch_arr_copy);

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

int mystrlen(char* str)
{
	int len = 0;
	int i = 0;
	while(str[i] != '\0')
	{
		len++;
		i++;
	}
	return len;
}

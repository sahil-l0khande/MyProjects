#include <stdio.h>
#include <string.h>

#define MAX_STRING_LENGTH 512

int main(void)
{
	// variable declarations
	char chArray[MAX_STRING_LENGTH];
	int str_length = 0, i;
	int word_count = 0, space_count = 0;
	// code
	
	printf("\n\n");
	printf("Enter a string : \n\n");
	fgets(chArray, 10, stdin);

	str_length = mystrlen(chArray);

	for (i = 0; i < str_length; i++)
	{
		switch (chArray[i])
		{
			case 32:
				space_count++;
				break;
			default:
				break;
		}
	}

	word_count = space_count + 1;
	printf("\n\n");
        printf("String entered by you is : \n\n");
	printf("%s\n", chArray);

	printf("\n\n");
        printf("Number of spaces in the input string = %d\n\n", space_count);
        printf("Number of words in the input string = %d\n\n", word_count);

	return (0);
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

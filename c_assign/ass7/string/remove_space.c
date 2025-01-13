#include <stdio.h>
#include <string.h>

#define MAX_STRING_LENGTH 512

int main(void)
{
	// variable declarations
	char chArray[MAX_STRING_LENGTH], ch_removed_spaces[MAX_STRING_LENGTH];
	int str_length = 0, i, j;
	int word_count = 0, space_count = 0;
	// code
	
	printf("\n\n");
	printf("Enter a string : \n\n");
	fgets(chArray, 10, stdin);

	str_length = mystrlen(chArray);
	j = 0;
	for (i = 0; i < str_length; i++)
	{
		if (chArray[i] == ' ')
			continue;
		else
		{
			ch_removed_spaces[j] = chArray[i];
			j++;
		}
	}
	
	ch_removed_spaces[j] = '\0';
	printf("\n\n");
        printf("String entered by you is : \n\n");
	printf("%s\n", chArray);

	printf("\n\n");
	printf("String after removal of space is : %s \n\n", ch_removed_spaces);
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

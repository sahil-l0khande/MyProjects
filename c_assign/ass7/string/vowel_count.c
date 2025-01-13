#include <stdio.h>
#include <string.h>

#define MAX_STRING_LENGTH 512

int main(void)
{
	// function prototype
	int mystrlen(char[]);
	
	// variable declarations
	char chArray[MAX_STRING_LENGTH];

	int len = 6, i;
	int count_a = 0, count_e = 0, count_i = 0, count_o = 0, count_u = 0; 
	// code
	
	printf("\n\n");
	printf("Enter a string : \n\n");
	scanf("%s", chArray);
	
	printf("\n\n");
        printf("String entered by you is : \n\n");
	printf("%s\n", chArray);

	int str_length = mystrlen(chArray);
	for (i = 0; i < str_length; i++)
	{
		switch (chArray[i])
		{
			case 'A':
			case 'a':
				count_a++;
				break;
			case 'E':
			case 'e':
				count_e++;
				break;
			case 'I':
			case 'i':
				count_i++;
				break;
			case 'O':
			case 'o':
				count_o++;
				break;
			case 'U':
			case 'u':
				count_u++;
				break;
			default:
				break;
		}
	}

	printf("\n\n");
	printf("In the string entered by you, the vowels and the number of their occurences are as follows : \n\n");
	printf("'A' has occured = %d times !!!\n\n", count_a);
	printf("'E' has occured = %d times !!!\n\n", count_e);
	printf("'I' has occured = %d times !!!\n\n", count_i);
	printf("'O' has occured = %d times !!!\n\n", count_o);
	printf("'U' has occured = %d times !!!\n\n", count_u);


	return (0);
}


int mystrlen(char str[])
{
	// varaible declarations
	int j;
	int len = 0;

	for (j = 0; j  < MAX_STRING_LENGTH;j++)
	{
		if(str[j] == '\0')
			break;
		else 
			len++;
	}
	return len;
}

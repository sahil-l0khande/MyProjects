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

	mystrcat(chArray,ch_arr_cat);
	
	printf("\n\n");
        printf("String entered by you is : \n\n");
	printf("%s\n", ch_arr_cat);

	printf("\n\n");
        printf("Copied string is : %s\n", chArray);

	return (0);
}

void mystrcat(char dst[], char src[])
{
	// function prototype
	int mystrlen(char[]);

	// variable declarations
	int src_len = 0, dst_len = 0;

	int i, j;

	// code
	
	src_len = mystrlen(src);
	dst_len = mystrlen(dst);

	for(i = dst_len, j = 0; j < src_len; i++, j++)
	{
		dst[i] = src[j];
	}
	dst[i] = '\0';
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

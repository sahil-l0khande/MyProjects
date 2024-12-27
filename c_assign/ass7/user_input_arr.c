#include <stdio.h>

#define INT_ARRAY_NUM_ELEMENTS 5
#define FLOAT_ARRAY_NUM_ELEMENTS 3
#define CHAR_ARRAY_NUM_ELEMENTS 15

int main(void)
{
	// variable declarations
	int i_arr[INT_ARRAY_NUM_ELEMENTS];
	float f_arr[FLOAT_ARRAY_NUM_ELEMENTS];
	char c_arr[CHAR_ARRAY_NUM_ELEMENTS];
	int i, num;

	// Code

	// **************** Array input ***************
	printf("\n\n");
	printf("Enter elements for 'integer' array : \n");
	for(int i = 0; i < INT_ARRAY_NUM_ELEMENTS; i++) 
		scanf("%d", &i_arr[i]);

	printf("\n\n");
	printf("Enter elements for 'float' array : \n");
	for(int i = 0; i < FLOAT_ARRAY_NUM_ELEMENTS; i++) 
		scanf("%f", &f_arr[i]);
	
	printf("\n\n");
	printf("Enter elements for 'character' array : \n");
	for(int i = 0; i < CHAR_ARRAY_NUM_ELEMENTS; i++) 
	{
		c_arr[i] = getchar();
		printf("%c\n", c_arr[i]);
	}

	// ******************** Array output **********************

	printf("\n\n");
	printf("'integer' array : \n\n");
	for(int i = 0; i < INT_ARRAY_NUM_ELEMENTS; i++) 
		printf("%d\n", i_arr[i]);

	printf("\n\n");
	printf("'float' array : \n");
	for(int i = 0; i < FLOAT_ARRAY_NUM_ELEMENTS; i++) 
		printf("%f\n", f_arr[i]);
	
	printf("\n\n");
	printf("'character' array : \n");
	for(int i = 0; i < CHAR_ARRAY_NUM_ELEMENTS; i++) 
		printf("%c\n", c_arr[i]);

	return (0);
}
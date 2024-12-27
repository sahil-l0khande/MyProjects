#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, char* argv[], char* envp[])
{
	// variable declarations
	int i;
	int num;
	int sum = 0;

	// code
	
	if (argc == 1)
	{
		printf("\n\n");
		printf("No numbers given for addition !!! exitting now ...\n\n");
		printf("Usage : command line arguments application <first number> <second number> ...\n\n");
		exit(0);
	}

	printf("\n\n");
	printf("Sum of all integer command line arguments is : \n\n");
	for(i = 1; i < argc; ++i)
	{
		num = atoi(argv[i]);
		sum = sum + num;
	}

	printf("Sum = %d\n\n", sum);

	return (0);
}

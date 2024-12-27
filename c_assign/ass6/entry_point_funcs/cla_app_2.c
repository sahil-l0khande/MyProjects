#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[])
{
	// variable declarations
	
	int i;

	// code
	
	if(argc != 4)
	{
		printf("\n\n");
		printf("Invalid Usage  !!! exitting now ...\n\n");
		printf("Usage : command line arguments application <first name> <middle name> <surname> ...\n\n");
		exit(0);
	}
	
	printf("\n\n");
	printf("Your full name is : ");
	for(i = 1; i < argc; ++i)
	{
		printf("%s ", argv[i]);
	}

	printf("\n\n");

	return (0);
}

#include <stdio.h>

int main(int argc, char* argv[], char *envp[])
{
	// code
	int i;	
	printf("\n\n");
	printf("Hello World !!!\n");
	printf("Number of command line arguments = %d\n\n", argc);
	
	printf("Command line arguments passed to this program are : \n\n");

	for(i = 0; i < argc; i++) {
		printf("Cmd line args no %d = %s\n", (i+1), argv[i]);
	}

	printf("\n\n");

	printf("First 20 vars passed to this program are : \n\n");
	for(i = 0; i < 20;i++)
	{
		printf("Env var no %d = %s\n", (i+1), envp[i]);
	}

	
	printf("\n\n");
	return (0);
}

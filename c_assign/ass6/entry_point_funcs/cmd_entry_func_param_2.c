#include <stdio.h>

int main(int argc, char* argv[])
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
	return (0);
}

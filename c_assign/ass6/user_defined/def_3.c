#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
	void myadd(int, int);

	int a, b, sum;

	printf("\n\n");
	printf("Enter the value for 'A' : ");
	scanf("%d", &a);

	printf("\n\n");
	printf("Enter the value for 'B' : ");
	scanf("%d", &b);
	
	myadd(a, b);
	return (0);
}

void myadd(int a, int b)
{
		
	int sum = a + b;
	
	printf("\n\n");
	printf("Sum of %d and %d = %d\n", a, b, sum);
}

#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
	void myadd(void);

	myadd();
	return (0);
}

void myadd(void)
{
	int a, b, sum;

	printf("\n\n");
	printf("Enter the value for 'A' : ");
	scanf("%d", &a);

	printf("\n\n");
	printf("Enter the value for 'B' : ");
	scanf("%d", &b);
	
	sum = a + b;
	
	printf("\n\n");
	printf("Sum of %d and %d = %d\n", a, b, sum);
}

#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
	int myadd(void);

	int sum = myadd();
	printf("\n\n");
	printf("Sum = %d\n", sum);
	return (0);
}

int myadd(void)
{
	int a, b, sum;

	printf("\n\n");
	printf("Enter the value for 'A' : ");
	scanf("%d", &a);

	printf("\n\n");
	printf("Enter the value for 'B' : ");
	scanf("%d", &b);
	
	sum = a + b;
	return sum;
}

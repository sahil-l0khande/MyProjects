#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
	int myadd(int, int);
	int mysub(int, int);
	int mymul(int, int);
	int mydiv(int, int);

	int a, b, sum, mul, div, sub;

	printf("\n\n");
	printf("Enter the value for 'A' : ");
	scanf("%d", &a);

	printf("\n\n");
	printf("Enter the value for 'B' : ");
	scanf("%d", &b);
	
	sum = myadd(a, b);
	sub = mysub(a, b);
	div = mydiv(a, b);
	mul = mymul(a, b);
	printf("\n\n");
	printf("Sum of %d and %d = %d\n", a, b, sum);
	
	printf("\n\n");
	printf("Sub of %d and %d = %d\n", a, b, sub);
	
	printf("\n\n");
	printf("multiplication of %d and %d = %d\n", a, b, mul);
	
	printf("\n\n");
	printf("Division of %d and %d = %d\n", a, b, div);
	return (0);
}

int myadd(int a, int b)
{
		
	int sum = a + b;
	
	return sum;
}
int mymul(int a, int b)
{
		
	int mul = a * b;
	
	return mul;
}
int mysub(int a, int b)
{
		
	int sub = a - b;
	
	return sub;
}
int mydiv(int a, int b)
{
		
	int div = 0;
	
	if (a > b)
		div = a / b;
	else 
		div = b / a;
	
	return div;
}

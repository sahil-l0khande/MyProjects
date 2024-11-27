#include <stdio.h>

int main(void)
{
	// variable declarations
	
	int a;
	int b;
	int x;

	//code
	
	printf("\n\n");
	printf("Enter A number : ");
	scanf("%d",&a);

	printf("\n\n");
	printf("Enter another number : ");
	scanf("%d", &b);

	printf("\n\n");

	x = a;
	a += b;
	printf("Addition of A : %d and b : %d gives %d.\n", x, b, a);

	x = a;
	a -= b;
	printf("Subtraction if  A : %d and b : %d gives %d.\n", x, b, a);
	x = a;
	a *= b;
	
	printf("Multiplication of A : %d and b : %d gives %d.\n", x, b, a);

	x = a;
	a /= b;
	printf("Division of A : %d and b : %d gives quotient %d.\n", x, b, a);
	
	x = a;
	a %= b;
	printf("Division of A : %d and b : %d gives remainder %d.\n", x, b, a);


	printf("\n\n");

	return (0);
}

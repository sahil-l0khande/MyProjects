#include <stdio.h>

int main(void)
{
	// variable declarations
	
	int a;
	int b;
	int result;

	//code
	
	printf("\n\n");
	printf("Enter A number : ");
	scanf("%d",&a);

	printf("\n\n");
	printf("Enter another number : ");
	scanf("%d", &b);

	printf("\n\n");

	result = a + b;
	printf("Addition of A : %d and b : %d gives %d.\n", a, b, result);

	result = a - b;
	printf("Subtraction if  A : %d and b : %d gives %d.\n", a, b, result);
	result = a * b;
	printf("Multiplication of A : %d and b : %d gives %d.\n", a, b, result);
	result = a / b;
	printf("Division of A : %d and b : %d gives quotient %d.\n", a, b, result);
	result = a % b;
	printf("Division of A : %d and b : %d gives remainder %d.\n", a, b, result);


	printf("\n\n");

	return (0);
}

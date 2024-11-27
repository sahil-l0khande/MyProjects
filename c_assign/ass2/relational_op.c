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

	result = (a < b);
	printf("(a < b)  A : %d is less than  b : %d\t\t Answer = %d.\n", a, b, result);


	result = (a > b);
	printf("(a > b)  A : %d is greater than  b : %d\t\t Answer = %d.\n", a, b, result);

	result = (a <= b);
	printf("(a <= b)  A : %d is less than or equal to  b : %d\t\t Answer = %d.\n", a, b, result);

	result = (a >= b);
	printf("(a >= b)  A : %d is greater than or equal to  b : %d\t\t Answer = %d.\n", a, b, result);

	result = (a == b);
	printf("(a == b)  A : %d is equal to  b : %d\t\t Answer = %d.\n", a, b, result);

	result = (a != b);
	printf("(a != b)  A : %d is not equal  b : %d\t\t Answer = %d.\n", a, b, result);
	printf("\n\n");

	return (0);
}

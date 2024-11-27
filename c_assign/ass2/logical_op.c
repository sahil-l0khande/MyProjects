#include <stdio.h>

int main(void)
{
	// variable declarations
	
	int a;
	int b,c;
	int result;

	//code
	
	printf("\n\n");
	printf("Enter A number : ");
	scanf("%d",&a);

	printf("\n\n");
	printf("Enter another number : ");
	scanf("%d", &b);

	printf("\n\n");
	printf("Enter another number : ");
	scanf("%d", &c);
	printf("\n\n");

	result = (a <= b) && (b!= c);
	printf("LOGICAL AND && : Answer is tru if and only if both conditions are true. Ans is false if any one or both conditions are false \n");
	printf("A : %d is less than or equal to b : %d AND b:%d is not equal to c:%d\t\t asnwer = %d\n\n", a, b,b,c, result);

	result = (b >= a) || (a == c);
	printf("LOGICAL OR ||  : Answer is tru if any of  both conditions are true. Ans is false only if both conditions are false \n");
	printf("A : %d is greater than or equal to b : %d OR b:%d is not equal to c:%d\t\t asnwer = %d\n\n", b, a,a,c, result);
	
	result = !a;
	printf("A : %d and using logical not gives result %d.\n", a, result);

	result = !b;
	printf("B : %d and using logical not gives result %d.\n", b, result);

	result = !c;
	printf("C : %d and using logical not gives result %d.\n", c, result);

	result = (!(a <= b) && !(b != c));
	printf("Using logical not on (a <= b) and also on (b != c) ans then anding them afterwardds gives result %d.\n", result);

	printf("\n\n");

	result = !((b >= a) || (a == c));
	printf("Using logical not on (a <= b) and also on (b !- c) and then AND-ing them afterwards gives result %d.\n", result);

	printf("\n\n");

	return (0);
}

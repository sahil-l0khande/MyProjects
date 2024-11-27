#include <stdio.h>

int main(void)
{
	// code
	
	printf("\n\n");
	printf
		("*****************************************");
	printf("\n\n");

	printf("Hello world !!!\n\n");

	int a = 13;
	printf("integer decimal value of 'a' = %d\n", a);
	printf("integer octal value of 'a' = %o\n", a);
	printf("integer hexadecimal value of 'a' (Hexadecimal letters in lower case  = %x\n\n", a);

	printf("integer hexadecimal value of 'a' (Hexadecimal letters in upper case  = %X\n\n", a);
	char ch = 'A';
	printf("Character ch = %c\n", ch);
	char str[] = "AstroMediComp's Real Time Rendering Batch";
	printf("String str = %s\n\n", str);

	long num = 30121995L;
	printf("Long Integer = %ld\n\n", num);

	unsigned int b = 7;
	printf("Unsigned integer 'b' = %u\n\n", b);

	float f_num = 3012.1995f;
	printf("Float point number with just %%f 'f_num' = %f\n", f_num);
	
	printf("Float point number with  %%4.2f 'f_num' = %4.2f\n", f_num);
	printf("Float point number with just %%6.5f 'f_num' = %6.5f\n\n", f_num);

	double d_pi  = 3.14159265358979323846;
	printf("Double precision float point number without exponential = %g\n", d_pi);
	printf("Double precision float point number without exponential (lower case)= %e\n", d_pi);
	printf("Double precision float point number without exponential (Upper Case) = %E\n", d_pi);
	printf("Double Hexadecimal value of 'd_pi' (hexadecimal letters in lower case) = %a\n", d_pi);
	printf("Double Hexadecimal value of 'd_pi' (hexadecimal letters in upper case) = %A\n", d_pi);

	printf("*********************************************\n");

	printf("\n\n");

	return (0);

}




	
	

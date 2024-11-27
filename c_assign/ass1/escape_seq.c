#include <stdio.h>

int main(void)
{
	// code
	
	printf("\n\n");
	printf("Going on to next line...using \\n Escape sequence\n\n");
	printf("Demonstrating \t Horizontal \t tab \t using \\\" \\\" escape sequence !!!\n\n");
	printf("\'This is a double quoted output\" Done using \\\" \\\" escape sequence\n\n");
	printf("\' This is a single quoted output\' Done using \\\' \\\' escape sequence\n\n");
	printf("BACKSPACE turned to backspace\b using escape sequence \\b\n\n");

	printf("\r Demonstrating carriage return using \\r escape sequence\n");
	printf("\r Demonstrating \r carriage return using \\r escape sequence\n");
	printf("\r Demonstrating carriage \r return using \\r escape sequence\n\n");

	printf("Demonstrating \x41 using \\xhh escape sequence\n\n");
	printf("Demonstrating \102 using \\000 espace sequence\n\n");

	return (0);
}

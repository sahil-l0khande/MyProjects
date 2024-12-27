#include <stdio.h>

int main(void)
{
    // function prototypes
    void BinOfNum(unsigned int);

    //variable declarations

    unsigned int a;
    unsigned int num_bits;
    unsigned int result;
    

    // code
    printf("\n\n");
    printf("Enter An Integer = ");
    scanf("%u", &a);

    printf("\n\n");
    printf("By how many bits you want to right shift : ");
    scanf("%u", &num_bits);

    printf("\n\n\n");
    result = a >> num_bits;
    printf("Bitwise right shift-ing of \nA = %d (Decimal) and B = %d (Decimal) gives result %d (Decimal).\n\n", a, num_bits, result);

    BinOfNum(a);
    BinOfNum(result);

    return (0);
}

void BinOfNum(unsigned int dec)
{
    //  variable declarations
    unsigned int quotient,  remainder;
    unsigned int num;
    unsigned int bin[8];
    int i;

    // code 
    for(i = 0; i < 8; i++) {
        bin[i] = 0;
    }

    printf("The Binary form of the decimal integer %d is \t=\t", dec);
    num = dec;
    i = 7;

    while(num != 0) {
        quotient = num / 2;
        remainder = num % 2;
        bin[i] = remainder;
        num = quotient;
        i--;
    }

    for(i = 0; i < 8 ; i++)
        printf("%u", bin[i]);

    printf("\n\n");
}
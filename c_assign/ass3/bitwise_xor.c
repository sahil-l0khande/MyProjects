#include <stdio.h>

int main(void)
{
    // function prototypes
    void BinOfNum(unsigned int);

    //variable declarations

    unsigned int a;
    unsigned int b;
    unsigned int result;
    

    // code
    printf("\n\n");
    printf("Enter An Integer = ");
    scanf("%u", &a);

    printf("\n\n");
    printf("Enter Another Integer = ");
    scanf("%u", &b);

    printf("\n\n\n");
    result = a ^ b;
    printf("Bitwise XOR-ing of \nA = %d (Decimal) and B = %d (Decimal) gives result %d (Decimal).\n\n", a, b, result);

    BinOfNum(a);
    BinOfNum(b);
    BinOfNum(result);

    return (0);
}

void BinOfNum(unsigned int dec)
{
    unsigned int bin[8] = {0};
    int num, rem, quo;
    printf("Binary form of %d is \t=\t", dec);
     num = dec;
    int i = 7;

    while(num != 0) {
        quo = num / 2;
        rem = num % 2;
        bin[i] = rem;
        num = quo;
        i--;
    }

    for(i = 0;i < 8; i++)
        printf("%u", bin[i]);

    printf("\n\n");
}
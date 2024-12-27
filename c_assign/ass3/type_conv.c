#include <stdio.h>

int main(void)
{
    int i, j;
    char ch_1, ch_2;

    int a, result_int;
    float f, result_float;

    int i_explicit;
    float f_explicit;

    // code
    printf("\n\n");

    // Intrconversion and implicit type-casting between 'char' and 'int' types

    i = 70;
    ch_1 = i;
    printf("i = %d\n", i);
    printf("character 1 after casting %c\n\n" , ch_1);

    ch_2 = 'Q';
    j = ch_2;
    printf("ch_2  = %c\n", ch_2);
    printf("j  after casting %d\n\n" , j);

    // IMplicit conversion of int to float

    a = 5;
    f = 7.8f;
    result_float = a + f;
    printf("int a = %d and float f = %f after adding gives float %f\n\n", a, f, result_float);

    result_int = a + f;
    printf("int a = %d and float f = %f after adding gives integer %d\n\n", a, f, result_int);

    // explicit type casting using casting operator

    f_explicit = 30.121995f;
    i_explicit = (int)f_explicit;
    printf("Before explicit type casting %f\n", f_explicit);
    printf("after explicit type casting %d\n", i_explicit);
}
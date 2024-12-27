#include <stdio.h>

int main(void)
{
    // var declarations

    float f;
    float f_num = 1.7f;

    // code

    printf("\n\n");

    for(f = f_num; f <= (f_num * 10.0f); f = f + f_num)
    {
        printf("\t%f\n", f);
    }

    printf("\n\n");

    return (0);
}
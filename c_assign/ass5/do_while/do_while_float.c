#include <stdio.h>

int main(void)
{
    // var declarations

    float f;
    float f_num = 1.7f;

    // code

    printf("\n\n");
    f = f_num; 
    do
    {
        printf("\t%f\n", f);
         f = f + f_num;
    } while(f <= (f_num * 10.0f));
    

    printf("\n\n");

    return (0);
}
#include <stdio.h>

int main(void)
{
    // var declarations

    int i,j;

    // code

    printf("\n\n");
    i = 1;
    while( i <= 10)
    {
        printf("\t i = %d\n", i);
        printf("----------\n");
        j = 1;
        while( j <= 5)
        {
            printf("\t j = %d\n", j);
            j++;
        }

        i++;
        printf("\n\n");
    }

    printf("\n\n");

    return (0);
}
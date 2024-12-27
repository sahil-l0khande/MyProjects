#include <stdio.h>

int main(void)
{
    // var declarations

    int i,j,k;

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
            printf("----------\n");
            k = 1;
            while( k <= 3)
            {
                printf("\t k = %d\n", k);
                k++;
            }
            printf("\n\n");
            j++;
        }

        
        printf("\n\n");
        i++;
    }

    printf("\n\n");

    return (0);
}
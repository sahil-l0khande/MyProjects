#include <stdio.h>

int main(void)
{
    // var declarations

    int i,j,k;

    // code

    printf("\n\n");
    i = 1;
    do
    {
        printf("\t i = %d\n", i);
        printf("----------\n");
        j = 1;
        do
        {
            printf("\t j = %d\n", j);
            printf("----------\n");
            k = 1;
            do
            {
                printf("\t k = %d\n", k);
                k++;
            }while( k <= 3);
            
            printf("\n\n");
            j++;
        } while( j <= 5);
        
        printf("\n\n");
        i++;
    } while( i <= 10);
    

    printf("\n\n");

    return (0);
}
#include <stdio.h>

int main(void)
{
    // var declarations

    int i,j;

    // code

    printf("\n\n");

    

    for(i = 1; i <= 10; i++)
    {
        if (i % 2 != 0) {
            printf("\t i = %d\n", i);
            printf("----------\n");

            for(j = 1; j <= 10; j++)
            {
                if(j % 2 == 0) {
                    printf("\t j = %d\n", j);
                } else {
                    continue;
                }

            }

            printf("\n\n");
        } else {
            continue;
        }
        
    }

    printf("\n\n");

    return (0);
}
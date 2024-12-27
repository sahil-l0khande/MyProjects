#include <stdio.h>

int main(void)
{
    // var declarations

    int i,j;

    // code

    printf("\n\n");

    for(i = 1; i <= 20; i++)
    {
        for(j = 1; j <= 20; j++)
        {
            if (j > i)
            {
                break;
            } else {
                printf("\t j = %d\n", j);
            }
        }

        printf("\n");
    }

    printf("\n\n");

    return (0);
}
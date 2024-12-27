#include <stdio.h>

int main(void)
{
    // var declarations

    int i;

    // code

    printf("\n\n");

    printf("Even numbers from 0 to 100\n\n");

    for(i = 1; i <= 100; i++)
    {
        if(i %2 != 0) {
            continue;
        } else {
            printf("\t%d\n", i);
        }
            
    }

    printf("\n\n");

    return (0);
}
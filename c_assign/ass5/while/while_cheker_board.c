#include <stdio.h>

int main(void)
{
    // var declarations

    int i, j, c;

    // code

    printf("\n\n");
    i = 1;
    while( i < 64)
    {
        j = 1;
        while( j < 64)
        {
            c = ((i & 0x8) == 0) ^ ((j & 0x8) == 0);

            if ( c == 0)
                printf(" ");
            
            if ( c == 1)
                printf("*");

            j++;
        }
        
        i++;
    }

    printf("\n\n");

    return (0);
}
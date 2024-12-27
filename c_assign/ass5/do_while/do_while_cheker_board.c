#include <stdio.h>

int main(void)
{
    // var declarations

    int i, j, c;

    // code

    printf("\n\n");
    i = 1;
    do
    {
        j = 1;
        do
        {
            c = ((i & 0x8) == 0) ^ ((j & 0x8) == 0);

            if ( c == 0)
                printf(" ");
            
            if ( c == 1)
                printf("*");

            j++;
        } while( j < 64);
        
        
        i++;
    } while( i < 64);


    printf("\n\n");

    return (0);
}
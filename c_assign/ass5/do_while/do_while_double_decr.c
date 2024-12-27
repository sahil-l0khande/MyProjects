#include <stdio.h>

int main(void)
{
    // var declarations

    int i,j;

    // code

    printf("\n\n");
    i = 10;
    j = 100;
    printf("printing digits 1 to 10 and 10 to 100: \n\n");
    do
    {
        printf("\t%d\t%d\n", i, j);
        i--;
        j = j - 10;
    } while( i >= 1, j >= 10);
    

    printf("\n\n");

    return (0);
}
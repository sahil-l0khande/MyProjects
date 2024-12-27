#include <stdio.h>

int main(void)
{
    // var declarations

    int i,j;

    // code

    printf("\n\n");

    printf("printing digits 1 to 10 and 10 to 100: \n\n");
    for(i = 10, j = 100; i >= 1, j >= 10; i--, j = j - 10)
    {
        printf("\t%d\t%d\n", i, j);
    }

    printf("\n\n");

    return (0);
}
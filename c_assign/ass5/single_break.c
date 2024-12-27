#include <stdio.h>

int main(void)
{
    // var declarations

    int i;
    char ch;

    // code

    printf("\n\n");

    printf("Printing even numbers from 1 to 100 for every user input. Exitting the loop when user enters character 'Q' or 'q' : \n\n");

    for(i = 1; i <= 100; i++)
    {
        printf("\t%d\n", i);
        ch = getchar();
        if( ch == 'Q' || ch == 'q') {
            break;
        }
    }

    printf("\n\n");

    return (0);
}
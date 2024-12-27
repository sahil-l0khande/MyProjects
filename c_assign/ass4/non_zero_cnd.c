#include <stdio.h>

int main(void)
{
    // variable declarations 
    int a;

    // code

    printf("\n\n");
    a = 5;
    if(a) // positive
    {
        printf("if block 1 : %d\n\n", a);
    }


    a = -5;
    if(a) // negative
    {
        printf("if block 2 : %d\n\n", a);
    }


    a = 0;
    if(a) // zeo value
    {
        printf("if block 3 : %d\n\n", a);
    }
    printf("All threee if done \n\n");

    return (0);
}
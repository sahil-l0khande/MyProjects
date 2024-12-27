#include <stdio.h>

#define MAX_NUMBER(a, b) ((a > b) ? a : b)

int main(int argc, char *argv[], char *envp[])
{
    // variable declarations

    int inum1;
    int inum2;
    int iresult;

    float fnum1;
    float fnum2;
    float fresult;
    // code

    // comparing int values

    printf("\n\n");
    printf("Enter  integer number : \n\n");
    scanf("%d", &inum1);

    printf("\n\n");
    printf("Enter another integer number : \n\n");
    scanf("%d", &inum2);

    iresult = MAX_NUMBER(inum1, inum2);
    printf("\n\n");
    printf("Result of macro function MAX_NUMBER() = %d\n", iresult);
    printf("\n\n");

    printf("\n\n");
    printf("Enter  float number : \n\n");
    scanf("%f", &fnum1);

    printf("\n\n");
    printf("Enter another float number : \n\n");
    scanf("%f", &fnum2);

    fresult = MAX_NUMBER(fnum1, fnum2);
    printf("\n\n");
    printf("Result of macro function MAX_NUMBER() = %f\n", fresult);
    printf("\n\n");

    return (0);

}
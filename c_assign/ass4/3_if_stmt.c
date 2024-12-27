#include <stdio.h>

int main(void)
{
    // variable declarations 
    int num;

    // code
    
    printf("\n\n");
    printf("Enter the value of num : ");
    scanf("%d", &num);
    if(num < 0)
    {
        printf("Num = %d is less than 0 (Negative)\n\n", num);
    }

    if((num > 0) && (num <= 100))
    {
        printf("Num is between 1 and 100\n\n");
    }

    if((num > 100) && (num <= 200))
    {
        printf("Num is between 100 and 200\n\n");
    }

     if((num > 200) && (num <= 200))
    {
        printf("Num is between 200 and 200\n\n");
    }

     if((num > 300) && (num <= 400))
    {
        printf("Num is between 300 and 400\n\n");
    }
     if((num > 400) && (num <= 500))
    {
        printf("Num is between 400 and 500\n\n");
    }
     if(num > 500)
    {
        printf("Num is greater than 500\n\n");
    }
    return (0);
}
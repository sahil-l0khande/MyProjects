#include <stdio.h>
int main(void)
{
    // variable declarations
    char option, ch = '\0';

    // code
    printf("\n\n");
    printf("Enter q for quit \n\n");
    printf("Enter y to initiate loop \n\n");

    option = getchar();

    if(option == 'Y' || option == 'y')
    {
        do
        {
            printf("in loop...\n");
            ch = getchar();
            if(ch =='Q' || ch == 'q')
                break;
        }
        while(1);
        
    }

    printf("\n\n");
    printf("Exiting loop");
    printf("\n\n");
    
    return (0);
}
#include <stdio.h>

int main(void)
{
    // var declarations

    int i_num, num, i;

    // code

    printf("\n\n");

    printf("Enter an integer value from which iteration must begin : ");
    scanf("%d", &i_num);

    printf("How many digits you want to print from %d onwards : ", i_num);
    scanf("%d", &num);
    
    printf("printing digits from %d to %d\n\n", i_num, (i_num + num));
    i = i_num;
    do
    {
        printf("\t%d\n", i);
         i++;
    } while( i <= (i_num + num));
    

    printf("\n\n");

    return (0);
}
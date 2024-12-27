#include <stdio.h>

#define NUM_ELEMENTS 10

int main(void)
{
    // Varaible declarations
    int i_arr[NUM_ELEMENTS];
    int i, num, j, count = 0;

    // Code 
    printf("\n\n");
    printf("Enter integer elements for array : \n\n");
    for (i = 0; i < NUM_ELEMENTS; ++i) {
        scanf("%d", &num);
        if(num < 0)
            num  = -1*num;
        i_arr[i] = num;
    }

    printf("\n\n");
    printf("Arr elements are  : \n\n");
    for (i = 0; i < NUM_ELEMENTS; ++i) {
            printf("%d\n", i_arr[i]);
    }


    printf("\n\n");
    printf("Prime numbers are  : \n\n");
    for (i = 0; i < NUM_ELEMENTS; ++i) {
        for (j = 1; j <= i_arr[i]; ++j) {
        if((i_arr[i] % j) == 0)
            count++;
        }

        if(count == 2) {
            printf("%d\n", i_arr[i]);
        }

        count = 0;
    }
   
    return (0);
}
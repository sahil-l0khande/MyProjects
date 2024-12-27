#include <stdio.h>


void change_count_two(void)
{
    // Code
    extern int global_count;

    global_count = global_count + 1;
    printf("change_count_two() : value of global_count in file1 = %d\n", global_count);

}
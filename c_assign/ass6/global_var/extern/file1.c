#include <stdio.h>

extern int global_count;

void change_count_one(void)
{
    // Code
    global_count = global_count + 1;
    printf("change_count_one() : value of global_count in file1 = %d\n", global_count);

}
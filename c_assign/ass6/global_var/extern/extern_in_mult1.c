#include <stdio.h>

int global_count = 0;

int main(void)
{
    // function prototypes
    void change_count(void);
    void change_count_one(void);
    void change_count_two(void);

    // code

    printf("\n\n");

    change_count();
    change_count_one();
    change_count_two();

    printf("\n\n");

    return (0);
}

// GLOBAL SCOPE

void change_count(void)
{
    // code
    global_count = global_count + 1;
    printf(" global_count = %d\n", global_count);
}

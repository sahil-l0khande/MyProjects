#include <stdio.h>

int main(void)
{
    // function prototypes

    void change_count(void);

    // variable declarations
    extern int global_count;
    // code

    printf("\n\n");
        printf(" Value of global_count before change_count() = %d\n", global_count);

    change_count();
    printf(" Value of global_count after change_count() = %d\n", global_count);

    printf("\n\n");

    return (0);
}

// GLOBAL SCOPE
int global_count = 0;

void change_count(void)
{
    // 5
    global_count = 100;
    printf(" Value of global_count in change_count() = %d\n", global_count);
}

#include <stdio.h>

int global_count = 0;

int main(void)
{
    // function prototypes
    void change_count(void);
    // code
    int a = 5;
    printf("\n\n");
    printf("A %d\n\n", a);
    change_count();
change_count();
change_count();
    printf("\n\n");

    return (0);
}

// GLOBAL SCOPE

void change_count(void)
{
    // code
    static int local_count = 0;

    local_count = local_count + 1;
    printf(" local count = %d\n", local_count);
}

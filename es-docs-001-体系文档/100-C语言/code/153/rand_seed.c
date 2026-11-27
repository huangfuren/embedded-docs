#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("RAND_MAX = %d\n", RAND_MAX);

    srand(42);
    printf("srand(42) -> ");
    for (int i = 0; i < 5; i++) printf("%d ", rand());
    printf("\n");

    srand(42);
    printf("srand(42) again -> ");
    for (int i = 0; i < 5; i++) printf("%d ", rand());
    printf("\n");

    srand(7);
    printf("[1,6] dice x10 -> ");
    for (int i = 0; i < 10; i++) printf("%d ", rand() % 6 + 1);
    printf("\n");
    return 0;
}

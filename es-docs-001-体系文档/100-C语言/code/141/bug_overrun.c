#include <stdio.h>

int main(void)
{
    int a[4] = {0};
    a[4] = 12345;              /* out of bounds! compiles fine, runs wild */
    printf("wrote a[4]=12345, a[3]=%d (neighbor may be hit)\n", a[3]);
    return 0;
}

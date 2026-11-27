#include <stdio.h>

int main(void)
{
    int arr[3] = {10, 20, 30};
    int *pi = arr;            /* 指向 int */
    char *pc = (char *)arr;   /* 同一地址，按字节走 */

    printf("pi   = %p, pi+1   = %p  (差 %d)\n",
           (void*)pi, (void*)(pi + 1), (int)((char*)(pi + 1) - (char*)pi));
    printf("pc   = %p, pc+1   = %p  (差 %d)\n",
           (void*)pc, (void*)(pc + 1), (int)((pc + 1) - pc));
    printf("*(pi+1) = %d\n", *(pi + 1));
    printf("sizeof(pi) = %zu, sizeof(pc) = %zu\n", sizeof pi, sizeof pc);
    return 0;
}

#include <stdio.h>

int main(void)
{
    int    x = 42;
    int    arr[3] = {10, 20, 30};
    char   c = 'A';
    int   *p = &x;

    printf("addr of x       = %p\n", (void*)&x);
    printf("addr of x+field = %p  (next int is +4)\n", (void*)(&x + 1));
    printf("addr of arr[0]  = %p\n", (void*)&arr[0]);
    printf("addr of arr[1]  = %p  (int array step = %zu)\n", (void*)&arr[1], sizeof(int));
    printf("addr of arr[2]  = %p\n", (void*)&arr[2]);
    printf("addr of c       = %p\n", (void*)&c);
    printf("p = %p, *p = %d\n", (void*)p, *p);
    printf("arr[1] via index  = %d ; via *(arr+1) = %d\n", arr[1], *(arr + 1));
    return 0;
}

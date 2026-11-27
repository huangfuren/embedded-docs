#include <stdio.h>
#include <stdlib.h>

int g = 1;                          /* data segment */
static int s = 2;                   /* data segment */

int main(void)
{
    int l = 3;                      /* stack */
    static int sl = 4;              /* data segment */
    int *h = malloc(sizeof(int));   /* heap */
    if (h == NULL) { return 1; }    /* malloc 三纪律之一：判 NULL */
    *h = 5;

    printf("global  g  = %d at %p\n", g,  (void*)&g);
    printf("static  s  = %d at %p\n", s,  (void*)&s);
    printf("static sl  = %d at %p\n", sl, (void*)&sl);
    printf("local   l  = %d at %p   <- stack\n", l, (void*)&l);
    printf("heap   *h   = %d at %p   <- heap\n", *h, (void*)h);
    free(h);
    h = NULL;
    return 0;
}

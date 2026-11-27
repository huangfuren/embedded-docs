#include <stdio.h>
#include <string.h>

int main(void)
{
    char s[] = "hi";               /* h i NUL -> 3 bytes */
    char buf[3] = {'A', 'B', 'C'}; /* NO NUL sentinel! */
    char *t = "hi";                /* read-only literal */
    (void)t;                       /* strcpy(t, "x"); <- 若执行就是写只读区：雷 */

    printf("sizeof s = %zu, strlen(s) = %zu\n", sizeof s, strlen(s));
    printf("s[2] is NUL? -> %d\n", s[2] == 0);
    printf("printing buf (8 raw bytes) -> ");
    for (int i = 0; i < 8; i++) {
        unsigned char ch = (unsigned char)buf[i];
        putchar((ch >= 32 && ch < 127) ? ch : '.');
    }
    printf("   <- ABC plus stack garbage, random each run\n");
    return 0;
}

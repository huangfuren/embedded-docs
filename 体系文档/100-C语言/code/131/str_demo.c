#include <stdio.h>
#include <string.h>

int main(void)
{
    char a[] = {'a', 'b', 'c', 'd', '\0'}; // 手写哨兵：没问题但麻烦
    char b[4] = {'t', 'o', 'm'};           // 指定长度须 > 字符个数：自动补 \0
    char c[] = {'j', 'a', 'c', 'k'};       // 没有 \0：危险
    char d[] = {"lucy"};                   // 没问题不推荐
    char e[] = "lily";                     // 最推荐

    printf("a=%s b=%s d=%s e=%s\n", a, b, d, e);
    printf("c=%s  <- 无 \\0, 输出连到内存中下一个 \\0 才停\n", c);

    char s[] = "How are you!";
    printf("sizeof s = %zu (含 \\0)\n", sizeof s);
    printf("strlen(s) = %zu (有效字符)\n", strlen(s));
    return 0;
}

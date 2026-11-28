/* binary.c —— 补码为什么是补码：用 4 位把三种表示摆在一起看
 * 用途：200 板块 211 册 §211.2、§211.3 实测
 * 编译：gcc -Wall binary.c -o binary.exe
 */
#include <stdio.h>
#include <limits.h>

/* 把 4 位值写成 4 个二进制字符，out 至少 5 字节 */
static void bits4(unsigned v, char out[5])
{
    for (int i = 0; i < 4; i++)
        out[i] = ((v >> (3 - i)) & 1u) ? '1' : '0';
    out[4] = '\0';
}

int main(void)
{
    printf("  v  | 补码 | 原码 | 反码\n");
    printf("-----+------+------+------\n");
    for (int v = -8; v <= 7; v++) {
        unsigned twos = (unsigned)v & 0xFu;     /* 补码 = 硬件里的位模式 */
        char t[5], s[5], o[5];
        bits4(twos, t);
        if (v >= 0) {
            bits4((unsigned)v, s);              /* 正数：三种表示完全相同 */
            bits4((unsigned)v, o);
        } else if (v > -8) {
            bits4(0x8u | (unsigned)(-v), s);    /* 原码：符号位 1 + 绝对值 */
            bits4((~twos) & 0xFu, o);           /* 反码：补码按位取反 */
        } else {
            s[0] = '-'; s[1] = '-'; s[2] = '\0';/* -8 在原码/反码里表示不出来 */
            o[0] = '-'; o[1] = '-'; o[2] = '\0';
        }
        printf(" %3d |  %s |  %s |  %s\n", v, t, s, o);
    }

    printf("\n32 位实测边界\n");
    printf("INT_MAX  = %d  (0x%08X)\n", INT_MAX, (unsigned)INT_MAX);
    printf("INT_MIN  = %d  (0x%08X)\n", INT_MIN, (unsigned)INT_MIN);
    printf("UINT_MAX = %u  (0x%08X)\n", UINT_MAX, UINT_MAX);

    int t = INT_MAX;    /* 用变量，避免编译器对常量表达式报 -Woverflow */
    printf("INT_MAX + 1 = %d   <- 有符号溢出是 UB，本机回绕到最小值\n", t + 1);
    unsigned z = 0;
    printf("0u - 1      = %u   <- 无符号回绕是良定义\n", z - 1);

    int a = -5;
    printf("\n补码自洽：~(-5) + 1 = %d（应等于 5）\n", ~a + 1);
    printf("同一串位模式 0xFFFFFFFF：unsigned = %u, int = %d\n",
           0xFFFFFFFFu, (int)0xFFFFFFFFu);
    return 0;
}

/* ieee754.c —— 浮点数从出生起就在近似：把 32 位拆成符号/指数/尾数看
 * 用途：200 板块 212 册 §212.1~§212.3 实测
 * 编译：gcc -Wall ieee754.c -o ieee754.exe
 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

static void dump(float f)
{
    uint32_t u;
    memcpy(&u, &f, sizeof u);            /* 按位复制，不改变位模式 */
    unsigned sign = (u >> 31) & 1u;
    unsigned expo = (u >> 23) & 0xFFu;
    unsigned frac = u & 0x7FFFFFu;
    printf("%-14.9g sign=%u exp=0x%02X(%4d) frac=0x%06X bits=0x%08X\n",
           (double)f, sign, expo, (int)expo - 127, frac, u);
}

int main(void)
{
    printf("== 1) 位域拆解（单精度 1-8-23）==\n");
    dump(1.0f);
    dump(-2.5f);
    dump(0.1f);
    dump(1e10f);
    dump(3.4028235e38f);     /* FLT_MAX 附近 */

    printf("\n== 2) 0.1 到底存成了什么 ==\n");
    float  f  = 0.1f;
    double d  = 0.1;
    printf("float  0.1 = %.20g\n", (double)f);
    printf("double 0.1 = %.20g\n", d);
    printf("0.1f + 0.2f == 0.3f ? %d\n", (0.1f + 0.2f) == 0.3f);
    printf("fabs(0.1f+0.2f-0.3f) = %.10e\n", fabs((double)(0.1f + 0.2f) - 0.3));

    printf("\n== 3) 单精度的整数天花板 2^24 ==\n");
    float big = 16777216.0f;                 /* 2^24 */
    printf("2^24            = %.1f\n", (double)big);
    printf("2^24 + 1 == 2^24 ? %d\n", (big + 1.0f) == big);
    printf("(float)16777217 = %.1f\n", (double)(float)16777217);
    float nearly = 8388608.0f;               /* 2^23 */
    printf("2^23 + 1 == 2^23 + 2 ? %d  (2^23 附近最小间隔是 1)\n",
           (nearly + 1.0f) == (nearly + 2.0f));

    printf("\n== 4) 浮点的字节序 ==\n");
    float one = 1.0f;                        /* 位模式 0x3F800000 */
    unsigned char *p = (unsigned char *)&one;
    printf("1.0f 的 4 个字节自低地址起: %02X %02X %02X %02X\n", p[0], p[1], p[2], p[3]);
    printf("（小端：低字节在前；若为 3F 80 00 00 则是大端）\n");
    return 0;
}

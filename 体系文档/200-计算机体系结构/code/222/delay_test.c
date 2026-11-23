/* 用途：200 板块 222 册 §222.3 实测 —— 软件延时为什么算不准
 * 编译：gcc -O0 / -O1 / -O2 各编一版，对比同一段空循环的耗时
 */
#include <stdio.h>
#include <windows.h>

/* 高精度计时：clock() 在 MinGW 下分辨率常在毫秒级，会量出 0.000 s */
static double now_s(void)
{
    static LARGE_INTEGER freq;
    LARGE_INTEGER c;
    if (freq.QuadPart == 0)
        QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&c);
    return (double)c.QuadPart / (double)freq.QuadPart;
}

/* 普通空循环：编译器有权认定"没有副作用"，整段删掉 */
static void delay_plain(unsigned n)
{
    for (unsigned i = 0; i < n; i++)
        ;
}

/* volatile 空循环：每次都要真的访存，循环保得住，但速度极慢 */
static void delay_volatile(unsigned n)
{
    for (volatile unsigned i = 0; i < n; i++)
        ;
}

int main(void)
{
    const unsigned N = 10000000u;
    double t0, t1;

    t0 = now_s(); delay_plain(N);    t1 = now_s();
    printf("plain    n=%u : %.4f s\n", N, t1 - t0);

    t0 = now_s(); delay_volatile(N); t1 = now_s();
    printf("volatile n=%u : %.4f s\n", N, t1 - t0);

    return 0;
}

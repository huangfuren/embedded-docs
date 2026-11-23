/* 用途：200 板块 231 册 §231.1 实测 —— 工作集越大，单次访问越慢
 * 编译：gcc -O0 -Wall mem_step.c -o mem_step.exe
 * 思路：随机访问（破坏预取）逐档扩大工作集，量每档的单次访问耗时。
 *       本机对应"缓存装得下 / 装不下"，可类比 MCU 的 "片内 SRAM / 外扩存储"。
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define LINE  64          /* 一次只碰一行里的 1 个字节，跨步 64 */
#define HOPS  1000000u    /* 每档固定访问次数，各档才可比 */

static double now_s(void)
{
    static LARGE_INTEGER freq;
    LARGE_INTEGER c;
    if (freq.QuadPart == 0)
        QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&c);
    return (double)c.QuadPart / (double)freq.QuadPart;
}

static void shuffle(size_t *a, size_t n)
{
    for (size_t i = 0; i < n; i++) a[i] = i;
    for (size_t i = n - 1; i > 0; i--) {
        size_t j = (size_t)(rand() % (int)(i + 1));
        size_t t = a[i]; a[i] = a[j]; a[j] = t;
    }
}

int main(void)
{
    const size_t KB = 1024u, MB = 1024u * 1024u;
    const size_t sizes[] = { 4*KB, 64*KB, 512*KB, 4*MB, 32*MB, 128*MB };
    const int n = (int)(sizeof(sizes) / sizeof(sizes[0]));

    char   *buf = (char *)malloc(128u * MB);
    size_t *idx = (size_t *)malloc(128u * MB / LINE * sizeof(size_t));
    if (!buf || !idx) { printf("alloc failed\n"); return 1; }
    srand(2024);
    memset(buf, 0xA5, 128u * MB);   /* 填非零值，校验和才有意义 */

    unsigned long long sink = 0;
    printf("工作集        单次访问\n");
    printf("------------  ----------\n");

    for (int k = 0; k < n; k++) {
        size_t lines = sizes[k] / LINE;
        shuffle(idx, lines);

        double t0 = now_s();
        for (unsigned i = 0; i < HOPS; i++)
            sink += (unsigned char)buf[idx[i & (lines - 1)] * LINE];
        double t1 = now_s();

        printf("%7zu KB    %6.1f ns\n", sizes[k] / KB, (t1 - t0) * 1e9 / HOPS);
    }

    printf("\n校验和 sink = %llu\n", sink);
    printf("(随机访问；顺序访问时预取器会把差异抹平)\n");
    free(buf);
    free(idx);
    return 0;
}

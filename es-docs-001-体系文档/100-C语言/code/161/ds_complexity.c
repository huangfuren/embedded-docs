#include <stdio.h>

/* 七种阶的实测演示：n=1000 时各函数的基本操作计数 */
long long c1, c2, c3, c4, c5, c6, c7;

void O1(int n) /* 常量阶：执行次数与 n 无关 */
{
    c1 = 1;
}

void On(int n) /* 线性阶：单层循环 */
{
    for (int i = 0; i < n; i++)
        c2++;
}

void On2(int n) /* 平方阶：双层循环 */
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            c3++;
}

void On3(int n) /* 立方阶：三层循环 */
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                c4++;
}

void Ologn(int n) /* 对数阶：问题规模每次减半 */
{
    while (n > 1)
    {
        n = n / 2;
        c5++;
    }
}

void Onlogn(int n) /* 线性对数阶：n 轮 × 每轮减半 */
{
    for (int i = 0; i < n; i++)
    {
        int m = n;
        while (m > 1)
        {
            m = m / 2;
            c6++;
        }
    }
}

void Osqrt(int n) /* 平方根阶：循环到根号 n */
{
    for (long long i = 0; i * i < n; i++)
        c7++;
}

int main(void)
{
    int n = 1000;
    O1(n); On(n); On2(n); On3(n); Ologn(n); Onlogn(n); Osqrt(n);
    printf("n=%d 时基本操作次数：\n", n);
    printf("O(1)      : %lld\n", c1);
    printf("O(log2n)  : %lld\n", c5);
    printf("O(sqrt n) : %lld\n", c7);
    printf("O(n)      : %lld\n", c2);
    printf("O(nlog2n) : %lld\n", c6);
    printf("O(n^2)    : %lld\n", c3);
    printf("O(n^3)    : %lld\n", c4);
    return 0;
}

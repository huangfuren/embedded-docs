#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    // rand() 范围 [0, RAND_MAX]；换种子后每次运行序列不同
    srand((unsigned)time(NULL));

    for (int i = 0; i < 5; i++)
    {
        // 生成 [22, 94] 区间随机数：rand() % (n-m+1) + m
        int num = rand() % 73 + 22;
        printf("num = %d\n", num);
    }
    return 0;
}

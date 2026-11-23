#include <stdio.h>

/* 递归深度实测：递归的栈空间 = 深度 O(n)，循环版额外空间 O(1) */
long long max_depth = 0;

void recurse(int depth) /* 每层递归在栈上占一帧 */
{
    if (depth > max_depth)
        max_depth = depth;
    if (depth >= 1000) /* 出口：递到 1000 层 */
        return;
    recurse(depth + 1);
}

int main(void)
{
    recurse(1);
    printf("递归到 1000 层: 最大递归深度 = %lld 层（栈空间 O(n)）\n", max_depth);

    for (int i = 0; i < 1000; i++) /* 循环做同样多的步数 */
    {
        /* 循环不占栈帧 */
    }
    max_depth = 0;
    printf("循环做 1000 步: 最大递归深度 = %lld 层（额外空间 O(1)）\n", max_depth);
    return 0;
}

#include <stdio.h>

int main(void)
{
    // 二维数组：每个元素又是一维数组（2 行 3 列）
    int arr[][3] = {1, 2, 3, 4, 5, 6};

    // 三种查长度公式
    int total = sizeof arr / sizeof arr[0][0];    // 元素总数
    int rows  = sizeof arr / sizeof arr[0];       // 一维数组个数（行）
    int cols  = sizeof arr[0] / sizeof arr[0][0]; // 每个一维数组的元素数（列）
    printf("total=%d rows=%d cols=%d\n", total, rows, cols);

    // arr[1] 是第 2 个一维数组的地址，地址不可改：arr[1] = ... 编译不过

    // 双重 for 遍历
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("arr[%d][%d] = %d\n", i, j, arr[i][j]);
        }
    }
    return 0;
}

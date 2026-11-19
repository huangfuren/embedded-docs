#include <stdio.h>

int main(void)
{
    // 动态初始化：程序员定类型和长度，值是内存里的垃圾值
    int raw[3];
    printf("raw[0] = %d (垃圾值, 每次运行可能不同)\n", raw[0]);

    // 静态初始化：程序员定每个值，长度由计算机自动算
    int arr[] = {10, 20, 30, 40, 50};

    // 查长度：sizeof 公式（C 数组没有 .length 属性）
    int length = sizeof arr / sizeof arr[0];
    printf("length = %d\n", length);

    // 查元素、改元素
    printf("arr[2] = %d\n", arr[2]);
    arr[2] = 99;
    printf("改后 arr[2] = %d\n", arr[2]);

    // 遍历
    for (int i = 0; i < length; i++)
    {
        printf("arr[%d] = %d\n", i, arr[i]);
    }
    return 0;
}

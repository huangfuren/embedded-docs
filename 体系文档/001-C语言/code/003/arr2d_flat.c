#include <stdio.h>

int main(void)
{
    /* 证明：二维数组在内存里就是按一维顺序连续存放的 */
    int arr[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int (*ptr)[2][3] = &arr;  /* 指向整个二维数组的指针（数组指针正式讲解在 006 §6.3） */
    int (*p1)[3] = &arr[0];   /* 数组指针：指向第一行（此处只需知道 p1+1 跨一整行 12 字节） */
    int *p2 = &arr[0][0];     /* 指向第一个元素 */

    printf("ptr = %p\n", (void *)ptr);
    printf("p1  = %p\n", (void *)p1);
    printf("p2  = %p\n", (void *)p2);

    /* 关键证明：p2 当一维数组连续走 6 个元素，正好按行铺完 */
    printf("按一维方式连续读 6 个: ");
    for (int k = 0; k < 6; k++)
        printf("%d ", p2[k]);
    printf("\n");

    /* 每行首地址：行与行只差 3 个 int（12 字节），中间没有空隙 */
    for (int i = 0; i < 2; i++)
        printf("&arr[%d] = %p\n", i, (void *)&arr[i]);
    return 0;
}

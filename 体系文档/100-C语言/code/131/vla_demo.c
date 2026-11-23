#include <stdio.h>

int main(void)
{
    /* C99 变长数组 VLA：长度运行期才确定 */
    int len = 3;
    int arr[len]; /* 合法：len 是运行期变量 */
    for (int i = 0; i < len; i++)
        arr[i] = (i + 1) * 100;

    int n;
    printf("请输入数组长度: ");
    scanf("%d", &n);
    int user[n]; /* 长度来自用户输入——编译期根本不知道 */
    for (int i = 0; i < n; i++)
        user[i] = i;
    printf("user 长度 = %zu, user[%d] = %d\n", sizeof user / sizeof user[0], n - 1, user[n - 1]);
    printf("arr 长度 = %zu\n", sizeof arr / sizeof arr[0]);
    return 0;
}

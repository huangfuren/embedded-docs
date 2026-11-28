/* seg.c —— 一张可执行文件里，哪些数据要"装进镜像"，哪些只在上电时清零
 * 用途：200 板块 221 册 §221.2 实测
 * 三种编译：
 *   gcc -Wall seg.c -o seg_base.exe
 *   gcc -Wall -DWITH_BSS  seg.c -o seg_bss.exe
 *   gcc -Wall -DWITH_DATA seg.c -o seg_data.exe
 */
#include <stdio.h>

int g_init  = 42;      /* .data：初值要存进镜像，上电由启动代码搬进 RAM */
int g_zero;            /* .bss ：全零，镜像里不存，上电清零即可 */
const int g_const = 7; /* .rodata：只读，留在"程序区"不搬走 */

#ifdef WITH_BSS
int big_zero[1 << 20];           /* 4 MB 全零 —— 应只涨 bss，不涨文件 */
#endif
#ifdef WITH_DATA
int big_init[1 << 20] = {1};     /* 4 MB 带初值 —— 应只涨文件，不涨 bss */
#endif

int main(void)
{
    int local = 1;               /* 栈：函数返回即消失，与镜像无关 */

    printf("g_init  = %d @ %p\n", g_init,  (void *)&g_init);
    printf("g_zero  = %d @ %p\n", g_zero,  (void *)&g_zero);
    printf("g_const = %d @ %p\n", g_const, (void *)&g_const);
    printf("local   = %d @ %p\n", local,   (void *)&local);

#ifdef WITH_BSS
    printf("big_zero[0] = %d, big_zero[last] = %d\n",
           big_zero[0], big_zero[(1 << 20) - 1]);
#endif
#ifdef WITH_DATA
    printf("big_init[0] = %d, big_init[last] = %d\n",
           big_init[0], big_init[(1 << 20) - 1]);
#endif
    return 0;
}

/* addr_mode.c —— 五种寻址方式在汇编里长什么样
 * 用途：200 板块 221 册 §221.2 实测
 * 编译：gcc -O0 -Wall addr_mode.c -o addr_mode.exe
 * 反汇编：objdump -d -Mintel addr_mode.exe   （Intel 语法比 AT&T 好学）
 */
#include <stdio.h>

int g_arr[4] = {10, 20, 30, 40};
int g_x = 5;

/* 立即数：操作数就在指令里 */
int f_imm(void) { return 42; }

/* 寄存器：两个操作数都在寄存器 */
int f_reg(int a, int b) { return a + b; }

/* 直接（绝对）寻址：地址是个固定常量 */
int f_dir(void) { return g_x; }

/* 间接寻址：地址存在寄存器里 */
int f_ind(int *p) { return *p; }

/* 变址：基址 + 索引 × 元素大小 */
int f_idx(int i) { return g_arr[i]; }

/* 基址 + 常量偏移 */
int f_off(void) { return g_arr[2]; }

int main(void)
{
    printf("%d %d %d %d %d %d %d\n",
           f_imm(), f_reg(1, 2), f_dir(), f_ind(&g_x), f_idx(3), f_off(), g_arr[0]);
    return 0;
}

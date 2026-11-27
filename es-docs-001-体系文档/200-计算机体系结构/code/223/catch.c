/* catch.c —— 用"信号"模拟中断：主循环被打断，控制流跳进处理函数
 * 用途：200 板块 223 册 §223.1 实测
 * 编译：gcc -Wall catch.c -o catch.exe
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void on_int(int sig)                 /* 中断处理函数：被打断后跳到这里 */
{
    (void)sig;
    printf("\ncaught SIGINT - handler took over, exiting\n");
    exit(0);
}

int main(void)
{
    signal(SIGINT, on_int);          /* 注册：SIGINT 到来时跳 on_int */
    for (int round = 1; ; round++) {
        printf("working... round %d\n", round);
        fflush(stdout);              /* 不冲缓冲，崩溃/退出时这行可能丢 */
        for (volatile long i = 0; i < 20000000; i++) { }   /* 忙等一段 */
        if (round == 2) raise(SIGINT);                     /* 模拟 Ctrl+C（真实中断由 OS 递送） */
    }
    return 0;
}

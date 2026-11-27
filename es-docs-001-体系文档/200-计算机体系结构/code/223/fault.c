/* fault.c —— 中断是"外面来敲门"，异常是"自己踩了坑"
 * 用途：200 板块 223 册 §223.3 实测
 * 编译：gcc -O0 -Wall fault.c -o fault.exe
 * 运行：fault.exe fpe   （整数除零 -> 硬件异常）
 *        fault.exe segv  （解引用空指针 -> 硬件异常）
 *        fault.exe       （不加参数，看用法）
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

static const char *sig_name(int sig)
{
    switch (sig) {
    case SIGFPE:  return "SIGFPE  —— 算术故障（CPU 执行指令时自己发现）";
    case SIGSEGV: return "SIGSEGV —— 非法访存（CPU 的地址检查拒绝）";
    case SIGINT:  return "SIGINT  —— 外部打断（键盘 Ctrl+C，来自 CPU 之外）";
    default:      return "未知信号";
    }
}

static void on_sig(int sig)
{
    printf("\n[handler] 捕获信号 %d: %s\n", sig, sig_name(sig));
    printf("[handler] 控制流已离开 main，正在处理函数里\n");
    exit(1);
}

int main(int argc, char **argv)
{
    signal(SIGFPE,  on_sig);
    signal(SIGSEGV, on_sig);
    signal(SIGINT,  on_sig);

    if (argc > 1 && strcmp(argv[1], "fpe") == 0) {
        volatile int zero = 0;          /* volatile：别让编译器把 10/0 提前算掉 */
        printf("about to divide by zero...\n");
        fflush(stdout);                 /* 先冲缓冲，否则崩溃时这行会丢 */
        int x = 10 / zero;
        printf("x = %d  （这行不会打印）\n", x);
    } else if (argc > 1 && strcmp(argv[1], "segv") == 0) {
        printf("about to write through NULL...\n");
        fflush(stdout);
        volatile int *p = NULL;
        *p = 1;
        printf("（这行不会打印）\n");
    } else {
        printf("用法: fault.exe fpe | segv\n");
    }
    return 0;
}

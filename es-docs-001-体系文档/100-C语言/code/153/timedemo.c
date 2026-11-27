#include <stdio.h>
#include <time.h>

int main(void)
{
    time_t now = time(NULL);
    printf("time(NULL) = %lld\n", (long long)now);
    printf("ctime      = %s", ctime(&now));

    struct tm *lt = localtime(&now);
    printf("local      = %04d-%02d-%02d %02d:%02d:%02d\n",
           lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday,
           lt->tm_hour, lt->tm_min, lt->tm_sec);

    clock_t c0 = clock();
    volatile double acc = 0;
    for (int i = 0; i < 10000000; i++) acc += i;
    clock_t c1 = clock();
    printf("acc = %.0f\n", (double)acc);
    printf("clock ticks = %ld, CLOCKS_PER_SEC = %ld\n", (long)(c1 - c0), (long)CLOCKS_PER_SEC);
    printf("elapsed = %.3f s\n", (double)(c1 - c0) / CLOCKS_PER_SEC);
    return 0;
}

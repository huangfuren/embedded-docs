#include <stdio.h>
#include <string.h>

int main(void)
{
    char buf[20] = "hello";
    char src[] = "world";

    // strlen：有效字符个数，忽略 \0
    printf("strlen(\"%s\") = %zu\n", buf, strlen(buf));

    // strcmp：返回 0 说明内容一致
    printf("strcmp(buf, \"hello\") = %d\n", strcmp(buf, "hello"));
    printf("strcmp(buf, \"world\") = %d\n", strcmp(buf, "world"));

    // strcat：把 src 拼接到 buf 尾部（受影响的是 buf）
    strcat(buf, " ");
    strcat(buf, src);
    printf("strcat 后: %s\n", buf);

    // strcpy：用 src 覆盖 buf（受影响的还是 buf）
    strcpy(buf, src);
    printf("strcpy 后: %s\n", buf);
    return 0;
}

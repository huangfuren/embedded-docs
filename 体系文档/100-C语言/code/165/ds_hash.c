#include <stdio.h>
#include <stdlib.h>

/* 哈希分桶思想延伸演示（取模分桶 + 链表挂冲突） */
#define BUCKETS 5

typedef struct Node
{
    int key;
    int value;
    struct Node *next; /* 同一个桶里的冲突元素串成链表 */
} Node;

Node *buckets[BUCKETS]; /* 桶数组：每个桶是一条链表的头 */

int hash(int key) /* 哈希函数：由程序员决定 */
{
    return key % BUCKETS;
}

void put(int key, int value)
{
    int b = hash(key);
    Node *cur = buckets[b];
    while (cur != NULL) /* 桶内链表：键已存在则覆盖（去重） */
    {
        if (cur->key == key)
        {
            cur->value = value;
            return;
        }
        cur = cur->next;
    }
    Node *n = (Node *)malloc(sizeof(Node)); /* 头插进桶 */
    n->key = key;
    n->value = value;
    n->next = buckets[b];
    buckets[b] = n;
}

int *get(int key) /* 找不到返回 NULL */
{
    Node *cur = buckets[hash(key)];
    while (cur != NULL)
    {
        if (cur->key == key)
            return &cur->value;
        cur = cur->next;
    }
    return NULL;
}

void print_buckets(void)
{
    for (int b = 0; b < BUCKETS; b++)
    {
        printf("桶%d: ", b);
        for (Node *cur = buckets[b]; cur != NULL; cur = cur->next)
            printf("key=%d(val=%d) -> ", cur->key, cur->value);
        printf("NULL\n");
    }
}

int main(void)
{
    put(10, 100); /* 10 % 5 = 0 → 桶0 */
    put(21, 200); /* 21 % 5 = 1 → 桶1 */
    put(32, 300); /* 32 % 5 = 2 → 桶2 */
    put(15, 500); /* 15 % 5 = 0 → 桶0：与 10 冲突，链表挂接 */
    put(10, 999); /* 键已存在 → 覆盖（去重逻辑） */
    print_buckets();
    int *v = get(21);
    printf("get(21) = %d\n", v ? *v : -1);
    v = get(99); /* 99 % 5 = 4 → 空桶 */
    printf("get(99) = %s\n", v ? "有" : "NULL（没找到）");
    return 0;
}

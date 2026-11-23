#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* 循环队列：front/rear 取模绕回 */
typedef struct
{
    int *data;
    size_t length;
    size_t capacity;
    size_t front; /* 队首：待删除索引 */
    size_t rear;  /* 队尾：待插入索引 */
} Queue;

void init_queue(Queue *queue, size_t init_capacity)
{
    queue->data = (int *)malloc(init_capacity * sizeof(int));
    queue->length = 0;
    queue->capacity = init_capacity;
    queue->front = 0;
    queue->rear = 0;
}

size_t get_length(Queue *queue)
{
    return queue->length;
}

void destroy_queue(Queue *queue)
{
    free(queue->data);
    queue->data = NULL;
    queue->length = 0;
    queue->capacity = 0;
    queue->front = 0;
    queue->rear = 0;
}

void en_queue(Queue *queue, int element)
{
    if (queue->length == queue->capacity) /* 满队列：拒绝入队 */
        return;
    queue->data[queue->rear] = element;
    queue->rear = (queue->rear + 1) % queue->capacity; /* 取模绕回 */
    queue->length++;
}

bool del_queue(Queue *queue, int *del_element)
{
    if (queue->length == 0)
        return false;
    *del_element = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->length--;
    return true;
}

void printf_queue(Queue *queue)
{
    if (queue->length == 0)
        return;
    for (size_t i = 0; i < queue->length; i++)
    {
        size_t index = (queue->front + i) % queue->capacity;
        printf("%d ", queue->data[index]);
    }
    printf("\n");
}

int main(void)
{
    Queue qu;
    init_queue(&qu, 6);
    en_queue(&qu, 100);
    en_queue(&qu, 200);
    en_queue(&qu, 300);
    en_queue(&qu, 400);
    en_queue(&qu, 500);
    en_queue(&qu, 600);
    en_queue(&qu, 700); /* 第 7 个：满队列拒绝 */
    printf("len=%zu\n", get_length(&qu));
    printf_queue(&qu);
    int d;
    del_queue(&qu, &d);
    del_queue(&qu, &d);
    del_queue(&qu, &d);
    printf("len=%zu\n", get_length(&qu));
    printf_queue(&qu);
    en_queue(&qu, 1000);
    en_queue(&qu, 2000);
    en_queue(&qu, 3000); /* 出 3 进 3：front/rear 绕回，空间复用 */
    printf("len=%zu\n", get_length(&qu));
    printf_queue(&qu);
    destroy_queue(&qu);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* 栈：数组底座 + 栈顶计数 */
typedef struct
{
    int *data;
    size_t length;   /* 栈中数据个数（栈顶 = length-1） */
    size_t capacity;
} Stack;

void init_stack(Stack *stack, size_t init_capacity)
{
    stack->data = (int *)malloc(init_capacity * sizeof(int));
    stack->length = 0;
    stack->capacity = init_capacity;
}

void resize_stack(Stack *stack, size_t new_capacity)
{
    stack->data = (int *)realloc(stack->data, new_capacity * sizeof(int));
    stack->capacity = new_capacity;
}

void destroy_stack(Stack *stack)
{
    free(stack->data);
    stack->data = NULL;
    stack->length = 0;
    stack->capacity = 0;
}

size_t get_length(Stack *stack)
{
    return stack->length;
}

void push_stack(Stack *stack, int element)
{
    if (stack->length == stack->capacity)
        resize_stack(stack, stack->capacity * 2);
    stack->data[stack->length] = element;
    stack->length++;
}

bool pop_stack(Stack *stack, int *del_element)
{
    if (stack->length == 0)
        return false;
    *del_element = stack->data[stack->length - 1];
    stack->length--;
    return true;
}

void printf_stack(Stack *stack)
{
    if (stack->length == 0)
        return;
    for (size_t i = 0; i < stack->length; i++)
        printf("%d ", stack->data[i]);
    printf("\n");
}

int main(void)
{
    Stack st;
    init_stack(&st, 3);
    push_stack(&st, 10);
    push_stack(&st, 20);
    push_stack(&st, 30);
    printf("len=%zu\n", get_length(&st));
    printf_stack(&st);
    push_stack(&st, 40); /* 容量 3 装不下 → 扩容 */
    printf("len=%zu\n", get_length(&st));
    printf_stack(&st);
    int del_num;
    pop_stack(&st, &del_num);
    printf("pop = %d\n", del_num);
    pop_stack(&st, &del_num);
    printf("pop = %d\n", del_num);
    printf("len=%zu\n", get_length(&st));
    printf_stack(&st);
    destroy_stack(&st);
    return 0;
}

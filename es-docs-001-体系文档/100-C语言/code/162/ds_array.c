#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* 动态数组：结构体 + 全套 API */
typedef struct
{
    int *data;       /* 指向连续内存的指针 */
    size_t length;   /* 数据个数 */
    size_t capacity; /* 容量 */
} DynamicArray;

void init_array(DynamicArray *array, size_t init_capacity)
{
    array->data = (int *)malloc(init_capacity * sizeof(int));
    array->length = 0;
    array->capacity = init_capacity;
}

void resize_array(DynamicArray *array, size_t new_capacity)
{
    array->data = (int *)realloc(array->data, new_capacity * sizeof(int));
    array->capacity = new_capacity;
}

void destroy_array(DynamicArray *array)
{
    free(array->data);
    array->data = NULL;
    array->capacity = 0;
    array->length = 0;
}

size_t get_length(DynamicArray *array)
{
    return array->length;
}

void insert_at(DynamicArray *array, size_t index, int element)
{
    if (index > array->length) /* 插入允许 index == length（=尾插） */
        return;
    if (array->length == array->capacity)
        resize_array(array, array->capacity * 2);
    for (size_t i = array->length; i > index; i--)
        array->data[i] = array->data[i - 1];
    array->data[index] = element;
    array->length++;
}

void insert_end(DynamicArray *array, int element)
{
    insert_at(array, array->length, element);
}

bool delete_at(DynamicArray *array, size_t index, int *del_element)
{
    if (index >= array->length) /* 修正：索引等于长度也是越界 */
        return false;
    *del_element = array->data[index];
    for (size_t i = index; i < array->length - 1; i++)
        array->data[i] = array->data[i + 1];
    array->length--;
    return true;
}

bool delete_end(DynamicArray *array, int *del_element)
{
    if (array->length == 0) /* 修正：空表直接失败 */
        return false;
    return delete_at(array, array->length - 1, del_element);
}

void printf_array(DynamicArray *array)
{
    if (array->length == 0)
        return;
    for (size_t i = 0; i < array->length; i++)
        printf("%d ", array->data[i]);
    printf("\n");
}

int main(void)
{
    DynamicArray array;
    init_array(&array, 5);
    insert_at(&array, 0, 30);
    insert_at(&array, 0, 20);
    insert_at(&array, 0, 10);
    printf("len=%zu\n", get_length(&array));
    insert_end(&array, 40);
    insert_end(&array, 50);
    insert_end(&array, 60); /* 第 6 个元素：容量 5 装不下 → 扩容 */
    printf("len=%zu\n", get_length(&array));
    printf_array(&array);
    int del_num;
    delete_at(&array, 3, &del_num);
    printf("deleted arr[3] = %d\n", del_num);
    delete_end(&array, &del_num);
    printf("deleted end = %d\n", del_num);
    printf("len=%zu\n", get_length(&array));
    printf_array(&array);
    destroy_array(&array);
    return 0;
}

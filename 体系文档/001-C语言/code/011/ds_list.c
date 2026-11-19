#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* 单向链表：节点 + 链表头 + 全套 API */
typedef struct Node
{
    int data;          /* 数据域 */
    struct Node *next; /* 指针域：存下一个节点的地址 */
} Node;

typedef struct
{
    Node *header;  /* 指向第一个节点 */
    size_t length; /* 链表长度 */
} LinkedList;

void init_linked_list(LinkedList *list)
{
    list->header = NULL;
    list->length = 0;
}

void destroy_list(LinkedList *list)
{
    Node *current_node = list->header;
    while (current_node != NULL)
    {
        Node *free_node = current_node;
        current_node = current_node->next;
        free(free_node);
    }
    list->header = NULL;
    list->length = 0;
}

size_t get_length(LinkedList *list)
{
    return list->length;
}

Node *get_prev_node(LinkedList *list, size_t index)
{
    Node *prev_node = list->header;
    for (size_t i = 1; i < index; i++)
        prev_node = prev_node->next;
    return prev_node;
}

void insert_at(LinkedList *list, size_t index, int element)
{
    if (index > list->length) /* 插入允许 index == length（=尾插） */
        return;
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = element;
    if (index == 0)
    {
        new_node->next = list->header;
        list->header = new_node;
    }
    else
    {
        Node *prev_node = get_prev_node(list, index);
        new_node->next = prev_node->next;
        prev_node->next = new_node;
    }
    list->length++;
}

void insert_end(LinkedList *list, int element)
{
    insert_at(list, list->length, element);
}

bool delete_at(LinkedList *list, size_t index, int *del_element)
{
    if (index >= list->length) /* 修正：删除 index==length 也是越界 */
        return false;
    Node *del_node = NULL;
    if (index == 0)
    {
        del_node = list->header;
        list->header = list->header->next;
    }
    else
    {
        Node *prev_node = get_prev_node(list, index);
        del_node = prev_node->next;
        prev_node->next = prev_node->next->next;
    }
    *del_element = del_node->data;
    free(del_node);
    list->length--;
    return true;
}

bool delete_end(LinkedList *list, int *del_element)
{
    if (list->length == 0) /* 修正：空表直接失败 */
        return false;
    return delete_at(list, list->length - 1, del_element);
}

void get_value(LinkedList *list, size_t index, int *element)
{
    if (index >= list->length) /* 修正：获取 index==length 也是越界 */
        return;
    if (index != 0)
    {
        Node *prev_node = get_prev_node(list, index);
        *element = prev_node->next->data;
        return;
    }
    *element = list->header->data;
}

void edit_value(LinkedList *list, size_t index, int element)
{
    if (index >= list->length) /* 修正：修改 index==length 也是越界 */
        return;
    if (index != 0)
    {
        Node *prev_node = get_prev_node(list, index);
        prev_node->next->data = element;
        return;
    }
    list->header->data = element;
}

void printf_list(LinkedList *list)
{
    if (list->length == 0)
        return;
    Node *current_node = list->header;
    while (current_node != NULL)
    {
        printf("%d ", current_node->data);
        current_node = current_node->next;
    }
    printf("\n");
}

int main(void)
{
    LinkedList list;
    init_linked_list(&list);
    insert_at(&list, 0, 20);
    insert_at(&list, 0, 10);
    printf("len=%zu\n", get_length(&list));
    insert_end(&list, 30);
    printf("len=%zu\n", get_length(&list));
    printf_list(&list);
    int del_num;
    delete_at(&list, 2, &del_num);
    printf("deleted idx2 = %d\n", del_num);
    delete_end(&list, &del_num);
    printf("deleted end = %d\n", del_num);
    printf("len=%zu\n", get_length(&list));
    int element;
    get_value(&list, 0, &element);
    printf("arr[0] = %d\n", element);
    edit_value(&list, 0, 100);
    printf_list(&list);
    destroy_list(&list);
    return 0;
}

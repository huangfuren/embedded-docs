#include <stdio.h>

/* 冒泡排序：相邻比较，大数右沉 */
void bubble_sort(int *arr, int len)
{
    for (int i = 0; i < len - 1; i++)       /* 外层控制轮数 */
    {
        for (int j = 0; j < len - 1 - i; j++) /* 内层控制每轮比较次数 */
        {
            if (arr[j] > arr[j + 1])
            {
                int t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
        }
    }
}

/* 快速排序（讲义基础版：基准取首元素，相向双指针交换） */
void quick_sort(int *arr, int start, int end)
{
    if (start >= end)
        return;
    int low = start;
    int high = end;
    int key = arr[start]; /* 基准 */
    while (1)
    {
        while (low < high && arr[high] >= key)
            high--;
        while (low < high && arr[low] <= key)
            low++;
        if (low >= high)
            break;
        int t = arr[low];
        arr[low] = arr[high];
        arr[high] = t;
    }
    arr[start] = arr[high]; /* 基准归位 */
    arr[high] = key;
    quick_sort(arr, start, high - 1);
    quick_sort(arr, high + 1, end);
}

/* 快速排序（讲义优化版：预增减扫描式，high 从 end+1 起步） */
void quick_sort2(int *arr, int start, int end)
{
    if (start >= end)
        return;
    int low = start, high = end + 1;
    while (1)
    {
        while (low < end && arr[++low] <= arr[start])
            ;
        while (high > start && arr[--high] >= arr[start])
            ;
        if (low >= high)
            break;
        int t = arr[low];
        arr[low] = arr[high];
        arr[high] = t;
    }
    int t = arr[start];
    arr[start] = arr[high];
    arr[high] = t;
    quick_sort2(arr, start, high - 1);
    quick_sort2(arr, high + 1, end);
}

void print_arr(int *arr, int len)
{
    for (int i = 0; i < len; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main(void)
{
    int a[] = {9, -16, 40, 23, -30, -49, 25, 21, 30};
    int len = sizeof(a) / sizeof(a[0]);
    bubble_sort(a, len);
    printf("冒泡: ");
    print_arr(a, len);

    int b[] = {9, -16, 40, 23, -30, -49, 25, 21, 30};
    quick_sort(b, 0, len - 1);
    printf("快排: ");
    print_arr(b, len);

    int c[] = {9, -16, 40, 23, -30, -49, 25, 21, 30};
    quick_sort2(c, 0, len - 1);
    printf("快排优化版: ");
    print_arr(c, len);
    return 0;
}

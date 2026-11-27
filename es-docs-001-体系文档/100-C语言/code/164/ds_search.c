#include <stdio.h>

/* 顺序查找：从头到尾逐个比 */
int sequential_search(int *arr, int len, int target)
{
    for (int i = 0; i < len; i++)
    {
        if (target == arr[i])
            return i;
    }
    return -1;
}

/* 二分查找：前提有序，每次范围减半 */
int binary_search(int *arr, int len, int target)
{
    int start = 0;
    int end = len - 1;
    while (start <= end)
    {
        int mid = (start + end) / 2;
        if (target > arr[mid])
            start = mid + 1;
        else if (target < arr[mid])
            end = mid - 1;
        else
            return mid;
    }
    return -1;
}

int main(void)
{
    int arr[] = {10, 20, 30, 40, 50, 60, 70};
    int len = sizeof(arr) / sizeof(arr[0]);
    printf("二分找 60 : 索引 %d\n", binary_search(arr, len, 60));
    printf("二分找 90 : 索引 %d（-1 = 没找到）\n", binary_search(arr, len, 90));
    printf("顺序找 30 : 索引 %d\n", sequential_search(arr, len, 30));
    printf("顺序找 35 : 索引 %d（-1 = 没找到）\n", sequential_search(arr, len, 35));
    return 0;
}

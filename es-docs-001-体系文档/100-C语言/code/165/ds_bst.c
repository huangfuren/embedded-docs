#include <stdio.h>
#include <stdlib.h>

/* 二叉查找树（BST）顺序插入退化演示：均衡 vs 退化树高对照 */
typedef struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
} Node;

Node *insert(Node *root, int key) /* BST 插入：小往左、大往右 */
{
    if (root == NULL)
    {
        Node *n = (Node *)malloc(sizeof(Node));
        n->key = key;
        n->left = n->right = NULL;
        return n;
    }
    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    return root;
}

int height(Node *root, int depth, int *max_depth) /* 递归量树高（根的深度记 1） */
{
    if (root == NULL)
        return *max_depth;
    if (depth > *max_depth)
        *max_depth = depth;
    height(root->left, depth + 1, max_depth);
    height(root->right, depth + 1, max_depth);
    return *max_depth;
}

Node *build(int from, int to) /* 顺序插入 from..to */
{
    Node *root = NULL;
    for (int k = from; k <= to; k++)
        root = insert(root, k);
    return root;
}

int main(void)
{
    int mid[] = {4, 2, 6, 1, 3, 5, 7};
    Node *balanced = NULL;
    for (int i = 0; i < 7; i++)
        balanced = insert(balanced, mid[i]); /* 均衡序插入 */
    int max_depth = 0;
    height(balanced, 1, &max_depth);
    printf("均衡插入（4,2,6,1,3,5,7）: 7 个节点, 树高 = %d\n", max_depth);

    Node *degenerated = build(1, 7);
    max_depth = 0;
    height(degenerated, 1, &max_depth);
    printf("顺序插入（1,2,...,7）  : 7 个节点, 树高 = %d  <- 退化成链\n", max_depth);

    Node *big = build(1, 100);
    max_depth = 0;
    height(big, 1, &max_depth);
    printf("顺序插入（1..100）    : 100 个节点, 树高 = %d\n", max_depth);
    return 0;
}

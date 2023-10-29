// https://blog.csdn.net/zhuiyisinian/article/details/104920587
// 给定一串数值各不相同的非负整数值，求以该串数建立的完全二叉搜索树的层序遍历输出序列。

/*
 * 1. 如何表示存储整个完全二叉搜索树 -- 层序遍历输出 -- 使用数组
 * 2. 怎样将给定的各个整数值放入树中对应的正确位置上 -- 对数组排序后利用中序遍历方式插入结点
 */
#include <iostream>
#include <algorithm>
using namespace std;

int comp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

void InitArr(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        cin >> arr[i];
    }
    qsort(arr, size, sizeof(int), comp);
}

// 这里i用指针是为了保证i的值可以一直连贯的加下去
void makeCBST(int *tree, int *arr, int pos, int *i)
{
    if ((pos < 1) || (pos > tree[0]) || (*i == tree[0]))
    {
        return;
    }
    else
    {
        makeCBST(tree, arr, pos * 2, i);
        tree[pos] = arr[(*i)++];
        makeCBST(tree, arr, pos * 2 + 1, i);
    }
}
void PrintCBST(int *tree)
{
    for (int i = 1; i <= tree[0]; i++)
    {
        cout << tree[i] << " ";
    }
    cout << endl;
}

int main()
{
    int N;
    cin >> N;

    int *arr = new int[N];
    int *tree = new int[N + 1];
    int i = 0;
    tree[0] = N; // 用0号位存储数组的长度
    InitArr(arr, N);
    makeCBST(tree, arr, 1, &i);
    PrintCBST(tree);
}
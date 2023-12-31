#include <iostream>
#include <vector>
using namespace std;
#define MAXSIZE 10

typedef struct
{
    int r[MAXSIZE + 1]; // 0是哨兵
    int length;
} SqList;

void swap(SqList *L, int i, int j)
{
    int tmp = L->r[i];
    L->r[i] = L->r[j];
    L->r[j] = tmp;
}

void Print(SqList *L)
{
    for (int i = 1; i <= L->length; i++)
    {
        cout << L->r[i] << " ";
    }
    cout << endl;
}

void BubbleSort(SqList *L)
{
    int i, j;
    bool flag = true;
    for (i = 1; i <= L->length && flag; i++)
    {
        flag = false;
        for (j = L->length - 1; j >= i; j--)
        {
            if (L->r[j] > L->r[j + 1])
            {
                swap(L, j, j + 1);
                flag = true; // 没有任何一个元素需要上浮，说明所有元素都在正确的位置。 所以flag是false就直接break
            }
        }
    }
}

void SelectSort(SqList *L)
{
    for (int i = 1; i <= L->length; i++)
    {
        int minIdx = i;
        for (int j = i + 1; j <= L->length; j++)
        {
            if (L->r[minIdx] > L->r[j])
            {
                minIdx = j;
            }
        }
        if (minIdx != i)
        {
            swap(L, minIdx, i);
        }
    }
}

void InsertSort(SqList *L)
{
    int i, j;
    // 初始有一张牌，后面依次插入
    for (i = 2; i <= L->length; i++)
    {
        // 需要移动次序
        if (L->r[i] < L->r[i - 1])
        {
            L->r[0] = L->r[i]; // 设置哨兵
            for (j = i - 1; L->r[j] > L->r[0]; j--)
            {
                L->r[j + 1] = L->r[j];
            }
            L->r[j + 1] = L->r[0];
        }
    }
}

void siftDown(SqList *L, int n, int i)
{
    while (true)
    {
        int l = 2 * i;
        int ri = 2 * i + 1;
        int ma = i;
        if (l < n && L->r[l] > L->r[ma])
            ma = l;
        if (ri < n && L->r[ri] > L->r[ma])
            ma = ri;
        if (ma == i)
        {
            break;
        }
        swap(L, ma, i);
        i = ma;
    }
}

void HeapSort(SqList *L)
{
    // 建堆操作：堆化除叶节点以外的其他所有节点，构建的是大根堆
    for (int i = L->length / 2; i >= 1; i--)
    {
        siftDown(L, L->length / 2, i);
    }
    // 从堆中提取最大元素，循环 n-1 轮
    for (int i = L->length; i > 1; i--)
    {
        swap(L->r[1], L->r[i]);
        siftDown(L, i, 1);
    }
}

void merge(vector<int> &nums, int left, int mid, int right)
{
    vector<int> tmp(nums.begin(), nums.end());
    int leftPtr = left;
    int rightPtr = mid + 1;
    int k = left;
    while (leftPtr <= mid && rightPtr <= right)
    {
        if (tmp[leftPtr] < tmp[rightPtr])
        {
            nums[k++] = tmp[leftPtr];
            leftPtr++;
        }
        else
        {
            nums[k++] = tmp[rightPtr];
            rightPtr++;
        }
    }
    // 左边有剩余
    while (leftPtr <= mid)
    {
        nums[k++] = tmp[leftPtr++];
    }
    // 右边有剩余
    while (rightPtr <= right)
    {
        nums[k++] = tmp[rightPtr++];
    }
}

void mergeSort(vector<int> &nums, int left, int right)
{
    if (left >= right)
    {
        return;
    }
    int mid = left + (right - left) / 2;
    mergeSort(nums, left, mid);
    mergeSort(nums, mid + 1, right);
    merge(nums, left, mid, right);
}

void Print(const vector<int> &v)
{
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;
}

// driver code
int main()
{
    vector<int> v = {7, 3, 2, 6, 0, 1, 5, 4};
    mergeSort(v, 0, v.size() - 1);
    Print(v);
}

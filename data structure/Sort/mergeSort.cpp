#include <vector>
#include <iostream>
#include <random>
#include <algorithm>
using namespace std;

#define ElementType int

/*
9  1  5  3  4  2  6  8  7
 19    35    24    68  7
   1359        2468   7
        12345689    7
            123456789
* 1. 先划成大小为1的块--length = 1
* 2. 然后合并为大小为2的块--length = 2
* 3. 合并大小为4的块--length=4
* 4. ... 当length大小大于N时停止
*/

void Merge1(ElementType A[], ElementType TmpA[], int L, int R, int RightEnd)
{
    int LeftEnd = R - 1;
    int Tmp = L;
    int NumElements = RightEnd - L + 1;
    while (L <= LeftEnd && R <= RightEnd)
    {
        if (A[L] <= A[R])
        {
            TmpA[Tmp++] = A[L++];
        }
        else
        {
            TmpA[Tmp++] = A[R++];
        }
    }
    while (L <= LeftEnd)
    {
        TmpA[Tmp++] = A[L++];
    }
    while (R <= RightEnd)
    {
        TmpA[Tmp++] = A[R++];
    }
    for (int i = 0; i < NumElements; i++, RightEnd--)
    {
        A[RightEnd] = TmpA[RightEnd];
    }
}

// length表示合并大小为length的块
void Merge_pass(ElementType A[], ElementType TmpA[], int N, int length)
{
    int i;
    // 合并大小为length的块 相当于步骤1
    for (i = 0; i < N - 2 * length; i += 2 * length)
    {
        Merge1(A, TmpA, i, i + length, i + 2 * length - 1);
    }
    // 归并最后两个子列
    if (i + length < N)
    {
        Merge1(A, TmpA, i, i + length, N - 1);
    }
    // 转移到TmpA
    else
    {
        for (int j = i; j < N; j++)
            TmpA[j] = A[j];
    }
}
void Print(ElementType A[], int N)
{
    for (int i = 0; i < N; i++)
    {
        cout << A[i] << " ";
    }
    cout << endl;
}

void MergeSort(ElementType A[], int N)
{
    int length = 1;
    ElementType *TmpA = new ElementType[N];
    if (TmpA != nullptr)
    {
        // 分配内存成功
        while (length < N)
        {
            // Merge_pass将A分块排序后的结果复制给了TmpA
            Merge_pass(A, TmpA, N, length);
            length *= 2;
            cout << "length = " << length << ": ";
            Print(TmpA, N);
            // Merge_pass将TmpA分块排序后的结果复制给了A, 如果length超过了N，就直接将TmpA复制给A
            Merge_pass(TmpA, A, N, length);
            length *= 2;
            cout << "length = " << length << ": ";
            Print(A, N);
        }
        delete TmpA;
    }
    else
    {
        cout << "空间不足" << endl;
    }
}

int main()
{
    ElementType *A = new ElementType[9];
    A[0] = 9;
    A[1] = 1;
    A[2] = 5;
    A[3] = 3;
    A[4] = 4;
    A[5] = 2;
    A[6] = 6;
    A[7] = 8;
    A[8] = 7;
    MergeSort(A, 9);
    Print(A, 9);
}
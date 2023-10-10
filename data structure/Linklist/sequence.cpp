#include <iostream>
using namespace std;
#define MAXSIZE 1000
typedef int ElementType;

typedef struct
{
    ElementType Data[MAXSIZE];
    int Last;
} List;
List L, *PtrL;

List *MakeEmpty()
{
    List *PtrL = (List *)malloc(sizeof(List));
    PtrL->Last = -1;
    return PtrL;
}

int Length(List *L)
{
    return L->Last + 1;
}

ElementType FindKth(int K, List *L)
{
    return L->Data[K];
}

int Find(ElementType X, List *L)
{
    // 使用顺序查找
    for (int i = 0; i <= L->Last; i++)
    {
        if (X == L->Data[i])
        {
            return i;
        }
    }
    return -1;
}
void insert(ElementType X, int i, List *L)
{
    if (i < 0 || i > Length(L))
    {
        cout << "插入索引有误" << endl;
    }
    else
    {
        for (int j = L->Last; j >= i + 1; j--)
        {
            L->Data[j + 1] = L->Data[j];
        }
        L->Data[i] = X;
        L->Last++;
    }
}
void Delete(int i, List *L)
{
    if (i < 0 || i > Length(L))
    {
        cout << "插入下标有误" << endl;
    }
    else
    {
        for (int j = i + 1; j < Length(L); j++)
        {
            L->Data[j - 1] = L->Data[j];
        }
        L->Last--;
    }
}

void PrintList(List *L)
{
    for (int i = 0; i < Length(L); i++)
    {
        cout << L->Data[i] << " ";
    }
    cout << endl;
}

int main()
{
    List *PL = MakeEmpty();
    insert(3, 0, PL);
    insert(17, 1, PL);
    insert(2, 2, PL);
    insert(8, 3, PL);
    insert(9, 4, PL);
    insert(10, 5, PL);
    insert(21, 6, PL);
    insert(18, 7, PL);
    insert(16, 8, PL);
    Delete(3, PL);
    PrintList(PL);
}
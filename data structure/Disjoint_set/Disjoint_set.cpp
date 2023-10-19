#include < iostream>
using namespace std;
#define ElementType int

int MaxSize = 1000; // 定义数组的最大长度
typedef struct
{
    ElementType Data;
    int Parent;
} SetType;

// 查找某个元素(x)所在的集合
/*
 * 1. 在数组中查找data x是否存在
 *   a. 未找到，返回-1
 *   b. 找到，返回“最终”父母的下标
 */

int Find(SetType S[], ElementType X)
{
    for (int i = 0; i < MaxSize; i++)
    {
        if (S[i].Data == X)
        {
            int Parent = S[i].Parent;
            while (Parent > 0)
            {
                i = Parent;
                Parent = S[i].Parent;
            }
            return i;
        }
    }
    cout << "没有找到该元素" << endl;
    return -1;
}

// 集合的并运算
/*
 * 1. 找到X1和X2所属的集合
 * 2. 如果X1和X2不属于同一个集合，则让S[Root1].Parent = Root2;
 */

void Union(SetType S[], ElementType X1, ElementType X2)
{
    int root1, root2;
    root1 = Find(S, X1);
    root2 = Find(S, X2);
    if (root1 != root2)
    {
        S[root1].Parent = root2;
    }
}
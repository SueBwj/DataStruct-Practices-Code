#include <iostream>
using namespace std;

class UF
{
private:
    int count; // 记录有几个节点连通
    int *parent;
    // 新增一个数组记录树的重量
    int *size;

public:
    UF(int n)
    {
        count = n;
        parent = new int[n];
        size = new int[n];
        // 最初没颗树只有一个节点
        // 重量应该初始化为1
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
            size[i] = 1;
        }
    }
    void Union(int x, int y)
    {
        int rootx = Find(x);
        int rooty = Find(y);
        if (rootx != rooty)
        {
            // 小树接到大树下比较平衡 -- 减少查找次数
            if (size[rootx] > size[rooty])
            {
                parent[rooty] = rootx;
                size[rootx] += size[rooty];
            }
            else
            {
                parent[rootx] = rooty;
                size[rooty] += size[rootx];
            }
            count--;
        }
    }
    int Find(int x)
    {
        // 根节点的 parent == x
        while (parent[x] != x)
        {
            // 这一行代码用于树的压缩
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }
    int count()
    {
        return count;
    }
    bool connected(int x, int y)
    {
        return Find(x) == Find(y);
    }
};

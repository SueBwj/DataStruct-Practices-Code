#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
#define MAXSIZE 1000
int arr[MAXSIZE], T[MAXSIZE];

// 获取左子节点的个数
int getLeftNodes(int n)
{
    int height = floor(log(n + 1) / log(2));
    int x = n - pow(2, height) + 1;
    int num = ((int)pow(2, height - 1) - 1) + min((int)pow(2, height - 1), x);
    return num;
}

// 构造完全二叉搜索树
void buildCBT_BST_tree(int Aleft, int Aright, int root_idx)
{
    // n表示树的节点数量
    int n = Aright - Aleft + 1;
    if (n == 0)
        return;
    // 计算n个节点的树有多少个左子节点
    int L = getLeftNodes(n);
    T[root_idx] = arr[Aleft + L];
    int left_root_idx = root_idx * 2 + 1;
    int right_root_idx = root_idx * 2 + 2;
    // 递归解决左子树和右子树的构造
    buildCBT_BST_tree(Aleft, Aleft + L - 1, left_root_idx);
    buildCBT_BST_tree(Aleft + L + 1, Aright, right_root_idx);
}

// driver code
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    sort(arr, arr + n);
    buildCBT_BST_tree(0, n - 1, 0);
    for (int i = 0; i < n; i++)
    {
        cout << T[i] << " ";
    }
    cout << endl;
}
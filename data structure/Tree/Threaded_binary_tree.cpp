// 使用中序遍历线索化二叉树
#include <iostream>
using namespace std;

typedef enum
{
    Thread,
    Link
} PointerTag;

template <typename T>
struct TreeNode
{
    T data;
    TreeNode *left;
    TreeNode *right;
    PointerTag LTag;
    PointerTag RTag;
    TreeNode() : data(nullptr), left(nullptr), right(nullptr) {}
    TreeNode(T data) : data(data), left(nullptr), right(nullptr) {}
};

// type # means there is no children.
template <typename T>
// remember to add & before to truly change the tree or it will only change its copy.
void BuildTree(TreeNode<T> *&node)
{
    T data;
    cin >> data;
    if (data == '#')
    {
        // base case ：因为每个节点只会访问一次，确保不会无限循环
        return;
    }
    else
    {
        node = new TreeNode<T>(data);
        BuildTree(node->left);
        BuildTree(node->right);
    }
}
template <typename T>
TreeNode<T> *pre = nullptr; // 全局变量保存前继节点
template <typename T>
void InThreading(TreeNode<T> *node)
{
    if (node)
    {
        InThreading(node->left);
        if (node->left == nullptr)
        {
            node->LTag = Thread;
            node->left = pre<T>; // 指向前继
        }
        if (node->right == nullptr)
        {
            pre<T>->RTag = Thread;
            pre<T>->right = node; // 指向后继
        }
        pre<T> = node; // 记录前继节点。
        InThreading(node->right);
    }
}

// driver code
int main()
{
    TreeNode<char> *root = nullptr;
    BuildTree(root);
    InThreading(root);
}
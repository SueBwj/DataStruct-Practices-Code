// using preorder to build a tree
#include <iostream>
using namespace std;

template <typename T>
struct TreeNode
{
    T data;
    TreeNode *left;
    TreeNode *right;
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
void preorder(TreeNode<T> *root)
{
    if (root == nullptr)
    {
        return;
    }
    else
    {
        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }
}

// driver code
int main()
{
    TreeNode<char> *root = nullptr;
    BuildTree(root);
    preorder(root);
}
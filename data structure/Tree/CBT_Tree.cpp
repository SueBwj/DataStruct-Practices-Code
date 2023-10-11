#include <iostream>
#include <stdio.h>
using namespace std;

// 用数组构成CBT，i为父节点，则2*i+1为左子节点，2*i+2为右子节点
class Node
{
public:
    int key;
    Node *left;
    Node *right;
    int height;
    Node(int val) : key(val), left(nullptr), right(nullptr), height(1) {}
    Node() : key(0), left(nullptr), right(nullptr), height(0) {}
};

// i 表示数组下标，n表示数组元素数量
Node *Recursion_Insert(const int *arr, int i, int n)
{
    Node *root = nullptr;
    if (i < n)
    {
        if (root == nullptr)
        {
            root = new Node(arr[i]);
        }
        root->left = Recursion_Insert(arr, 2 * i + 1, n);
        root->right = Recursion_Insert(arr, 2 * i + 2, n);
    }
    return root;
}

// Function to print tree nodes in
// InOrder fashion
void inOrder(Node *root)
{
    if (root != NULL)
    {
        inOrder(root->left);
        cout << root->key << " ";
        inOrder(root->right);
    }
}

// Driver program to test above function
int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 6, 6, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    Node *root = Recursion_Insert(arr, 0, n);
    inOrder(root);
}

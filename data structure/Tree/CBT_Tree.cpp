#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
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

// queue insert
Node *Queue_Insert(vector<int> arr)
{
    if (arr.size() == 0)
    {
        return nullptr;
    }
    else
    {
        Node *root = new Node(arr[0]);
        queue<Node *> q;
        q.push(root);
        int i = 1;
        while (i < arr.size())
        {
            Node *cur = q.front();
            q.pop();
            if (i < arr.size())
            {
                Node *node = new Node(arr[i++]);
                cur->left = node;
                q.push(node);
            }
            if (i < arr.size())
            {
                Node *node = new Node(arr[i++]);
                cur->right = node;
                q.push(node);
            }
        }
        return root;
    }
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
    vector<int> arr = {1, 2, 3, 4, 5, 6, 6, 6, 6};
    Node *root = Queue_Insert(arr);
    inOrder(root);
}

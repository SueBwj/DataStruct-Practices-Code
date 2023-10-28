#include <iostream>
#include <stack>
#include <vector>
#include <queue>
using namespace std;
typedef struct TreeNode *BinTree;
typedef BinTree Position;
struct TreeNode
{
    int data;
    BinTree left;
    BinTree right;
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
    TreeNode() : data(0), left(nullptr), right(nullptr) {}
};

// 使用栈完成中序遍历
// 1. always left
// 2. left == nullptr then turn to right tree(then left)
void InOrderTraversal(BinTree BT)
{
    if (BT == nullptr)
        return;
    else
    {
        stack<BinTree> st;
        while (!st.empty() || BT)
        {
            while (BT)
            {
                st.push(BT);
                BT = BT->left;
            }
            if (!st.empty())
            {
                BT = st.top();
                st.pop();
                cout << BT->data << " ";
                BT = BT->right;
            }
        }
    }
    cout << endl;
}

// 判断current 是否为rt的孩子
BinTree Parent(BinTree rt, BinTree current)
{
    if (current == nullptr || rt == nullptr)
    {
        // nullptr不为rt的孩子
        return nullptr;
    }
    else
    {
        if (current == rt->left || current == rt->right)
        {
            return rt;
        }
        else
        {
            // 向左边寻找
            BinTree Left = Parent(rt->left, current);
            if (Left)
                return rt;
            // 向右边寻找
            BinTree Right = Parent(rt->right, current);
            if (Right)
                return rt;
            return nullptr;
        }
    }
}

// 先序遍历和中序遍历来确定一颗二叉树
/*
输入: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
输出: [3,9,20,null,null,15,7]
*/
int FindRootIdx(vector<int> &inorder, int val)
{
    for (int i = 0; i < inorder.size(); i++)
    {
        if (inorder[i] == val)
        {
            return i;
        }
    }
    cout << val << endl;
    cout << "cannot find the index of root." << endl;
    return -1;
}

// 根据前序遍历和中序遍历得到的数组构建tree。
TreeNode *buildTree(vector<int> preorder, vector<int> inorder)
{
    if (preorder.size() == 0 || inorder.size() == 0)
        return nullptr;
    BinTree root = new TreeNode(preorder[0]);
    if (preorder.size() == 1 && inorder.size() == 1)
    {
        return root;
    }
    int idx = FindRootIdx(inorder, preorder[0]);
    if (idx)
    {
        vector<int> LeftPreorder(preorder.begin() + 1, preorder.begin() + idx + 1);
        vector<int> RightPreorder(preorder.begin() + idx + 1, preorder.end());
        vector<int> LeftInorder(inorder.begin(), inorder.begin() + idx);
        vector<int> RightInorder(inorder.begin() + idx + 1, inorder.end());
        root->left = buildTree(LeftPreorder, LeftInorder);
        root->right = buildTree(RightPreorder, RightInorder);
        return root;
    }
    else
    {
        return nullptr;
    }
}

// 层序遍历树
void levelTraversal(BinTree root)
{
    if (root == nullptr)
    {
        return;
    }
    queue<BinTree> q;
    q.push(root);
    while (!q.empty())
    {
        BinTree tmp = q.front();
        cout << tmp->data << " ";
        q.pop();
        if (tmp->left)
        {
            q.push(tmp->left);
        }
        if (tmp->right)
        {
            q.push(tmp->right);
        }
    }
}

int main()
{
    // driver code of InOrderTraversal
    /*
            1
          2   3    output: 4 2 5 1 7 3
        4  5 7
    */
    BinTree root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(7);
    // InOrderTraversal(root);

    // driver code for Parent
    // if (Parent(root, root->left->right))
    // {
    //     cout << "Yes" << endl;
    // }

    // driver code using preorder and inorder vector to build tree.
    vector<int> preorder = {3, 9, 20, 15, 7};
    vector<int> inorder = {9, 3, 15, 20, 7};
    BinTree tree = buildTree(preorder, inorder);
    levelTraversal(tree);
}
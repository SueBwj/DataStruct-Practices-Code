#include <iostream>
#include <stack>
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

// using stack to implement inorder traversal
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
    InOrderTraversal(root);
}
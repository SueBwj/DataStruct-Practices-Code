// Reference https://www.geeksforgeeks.org/insertion-in-an-avl-tree/#
#include <iostream>
#include <cmath>
using namespace std;

// An AVL tree node
class Node
{
public:
    int key;
    Node *left;
    Node *right;
    int height;
    Node(int val) : key(val), left(nullptr), right(nullptr), height(0) {}
    Node() : key(0), left(nullptr), right(nullptr), height(0) {}
};

// Helper Functions

int getHeight(Node *n)
{
    if (!n)
    {
        return -1;
    }
    else
    {
        return n->height;
    }
}

int getBf(Node *root)
{
    if (root)
    {
        return getHeight(root->left) - getHeight(root->right);
    }
    return -1;
}

void preOrder(Node *root)
{
    if (root == nullptr)
    {
        return;
    }
    else
    {
        cout << root->key << ' ';
        preOrder(root->left);
        preOrder(root->right);
    }
}

int FindMin(Node *root)
{
    if (root->left == nullptr)
    {
        return root->key;
    }
    else
    {
        return FindMin(root->left);
    }
}

// left rotate
/*
 * 节点左旋转
 *  x             y
 *   \           /
 *    y   -->   x
 *   /           \
 *  t2            t2
 */

Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *t2 = y->left;

    // implete rotation
    y->left = x;
    x->right = t2;

    // update the nodes'height
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    // return the new root;
    return y;
}

// right rotate
/*
 * 节点右旋转
 *    y          x
 *   /            \
 *  x      -->     y
 *   \            /
 *    t2         t2
 */

Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *t2 = x->right;

    // implete rotation
    x->right = y;
    y->left = t2;

    // update the height
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    // return the new root;
    return x;
}

// balance AVLTree
Node *balanceRoot(Node *root, int key)
{
    // 获取根节点的平衡因子,来判断是否保持平衡
    int bf = getBf(root);

    // LL situation
    if (bf > 1 && key < root->left->key)
        return rightRotate(root);

    // RR situation
    if (bf < -1 && key > root->right->key)
        return leftRotate(root);

    // LR situation
    if (bf > 1 && key > root->left->key)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RL situation
    if (bf < -1 && key < root->right->key)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    // 依然保持平衡，不做处理，返回根节点
    return root;
}

Node *AVL_Insert(Node *root, int val)
{
    // 1.执行普通的二叉搜索树节点插入
    if (root == nullptr)
    {
        return new Node(val);
    }
    else
    {
        if (val > root->key)
        {
            root->right = AVL_Insert(root->right, val);
        }
        else
        {
            root->left = AVL_Insert(root->left, val);
        }
    }

    // 2.更新根节点的高度
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // 3. 返回平衡后的节点
    return balanceRoot(root, val);
}

Node *AVL_Delete(Node *root, int val)
{
    // 1.执行普通的删除操作
    if (root->key < val)
    {
        root->right = AVL_Delete(root->right, val);
    }
    else if (root->key > val)
    {
        root->left = AVL_Delete(root->left, val);
    }
    else if (val == root->key)
    {
        if (root->left && root->right)
        {
            root->key = FindMin(root->right);
            root->right = AVL_Delete(root->right, root->key);
        }
        else
        {
            Node *tmp = root;
            if (root->left)
            {
                root = root->left;
            }
            if (root->right)
            {
                root = root->right;
            }
            delete tmp;
        }
    }

    // 2.更新节点的高度
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // 3.返回平衡后的节点
    return balanceRoot(root, val);
}

// Driver Code
int main()
{
    Node *root = NULL;

    /* Constructing tree given in
    the above figure */
    root = AVL_Insert(root, 4);
    root = AVL_Insert(root, 2);
    root = AVL_Insert(root, 6);
    root = AVL_Insert(root, 1);
    root = AVL_Insert(root, 3);
    root = AVL_Insert(root, 5);
    root = AVL_Insert(root, 7);

    // /* The constructed AVL Tree would be
    //         9
    //     / \
    //     1 10
    //     / \ \
    // 0 5 11
    // / / \
    // -1 2 6
    // */

    // cout << "Preorder traversal of the "
    //         "constructed AVL tree is \n";
    // preOrder(root);

    // root = AVL_Delete(root, 10);

    // /* The AVL Tree after deletion of 10
    //         1
    //     / \
    //     0 9
    //     / / \
    // -1 5     11
    //     / \
    //     2 6
    // */

    // cout << "\nPreorder traversal after"
    //      << " deletion of 10 \n";
    preOrder(root);

    return 0;
}
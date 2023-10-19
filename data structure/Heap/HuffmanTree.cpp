#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template <typename T>
struct HuffmanTreeNode
{
    T weight;
    HuffmanTreeNode *left;
    HuffmanTreeNode *right;
    HuffmanTreeNode() = default;
    HuffmanTreeNode(int w) : weight(w), left(nullptr), right(nullptr) {}
};

template <typename T>
class MinHeap
{
private:
    vector<T> MinHeap; // 全局变量
    // 用数组构建堆，父母，左孩子和有孩子存在对应关系
    // 获取左孩子下标索引
    int left(int i)
    {
        return 2 * i + 1;
    }
    // 获取右孩子下标索引
    int right(int i)
    {
        return 2 * i + 2;
    }
    // 获取parent的下标索引
    int parent(int i)
    {
        return (i - 1) / 2;
    }

public:
    // 访问堆顶元素
    T peek()
    {
        if (MinHeap.size() <= 0)
        {
            throw out_of_range("the MinHeap is empty");
        }
        return MinHeap[0];
    }
    int size()
    {
        return MinHeap.size();
    }
    // 将元素加入堆中
    /*
     * 1. 将元素添加到数组尾。
     * 2. 在该节点所在的路径上从下到上恢复被破坏的堆结构 -- siftUp
     *   a. 如果子节点值大于父节点值，则交换
     *   b. 如果当前节点为父节点 || 子节点小于父节点则break
     */
    void siftUp(int i)
    {
        while (true)
        {
            int p = parent(i);
            if (i <= 0 || MinHeap[i]->weight > MinHeap[p]->weight)
            {
                break;
            }
            swap(MinHeap[i], MinHeap[p]);
            i = p;
        }
    }

    void push(T data)
    {
        MinHeap.push_back(data);
        siftUp(MinHeap.size() - 1);
    }

    // 将元素从堆中删除
    /*
     * 1. 将堆顶元素和最后一个元素进行交换
     * 2. 在该节点的路径上从上到下恢复堆的结构 -- siftDown
     *   a. 将当前节点与左右两个子节点进行比较，与最大的那个交换
     *   b. 当当前节点为叶子节点 || 当前节点大于左右两个叶子节点
     */
    void siftDown(int i)
    {
        while (true)
        {
            int nxt = i;
            int l = left(i);
            int r = right(i);
            if (l < MinHeap.size() && MinHeap[nxt]->weight > MinHeap[l]->weight)
                nxt = l;
            if (r < MinHeap.size() && MinHeap[nxt]->weight > MinHeap[r]->weight)
                nxt = r;
            if (i == nxt || (l >= MinHeap.size() && r >= MinHeap.size()))
            {
                break;
            }
            swap(MinHeap[i], MinHeap[nxt]);
            i = nxt;
        }
    }

    void pop()
    {
        if (MinHeap.size() < 0)
        {
            throw out_of_range("the MinHeap is empty.");
        }
        swap(MinHeap[0], MinHeap[MinHeap.size() - 1]);
        MinHeap.pop_back();
        siftDown(0);
    }
    // 向下堆化。
    void Down_Heapify(vector<T> nums)
    {
        MinHeap = nums;
        for (int i = parent(MinHeap.size() - 1); i >= 0; i--)
        {
            siftDown(i);
        }
    }
    // 一个个插入然后向上堆化
    void Insert_Heapify(vector<T> nums)
    {
        for (int i = 0; i < nums.size(); i++)
        {
            push(nums[i]);
        }
    }

    // helper functions
    void Print()
    {
        for (int i = 0; i < MinHeap.size(); i++)
        {
            cout << MinHeap[i] << " ";
        }
        cout << endl;
    }
};

template <typename T>
void Preorder(HuffmanTreeNode<T> *root)
{
    if (root == nullptr)
    {
        return;
    }
    cout << root->weight << endl;
    Preorder(root->left);
    Preorder(root->right);
}

HuffmanTreeNode<int> *CreateHuffman(MinHeap<HuffmanTreeNode<int> *> *&H)
{
    // 此时的H是已经包含权重信息的小根堆
    HuffmanTreeNode<int> *node = nullptr;
    while (H->size() > 1)
    {
        node = new HuffmanTreeNode<int>();
        HuffmanTreeNode<int> *node1 = H->peek();
        H->pop();
        HuffmanTreeNode<int> *node2 = H->peek();
        H->pop();
        node->left = node1;
        node->right = node2;
        node->weight = node1->weight + node2->weight;
        H->push(node);
    }
    return node;
}

// driver code
int main()
{
    // 用权重构造MinHeap;
    MinHeap<HuffmanTreeNode<int> *> *MH1 = new MinHeap<HuffmanTreeNode<int> *>();
    HuffmanTreeNode<int> *node1 = new HuffmanTreeNode<int>(1);
    HuffmanTreeNode<int> *node2 = new HuffmanTreeNode<int>(2);
    HuffmanTreeNode<int> *node3 = new HuffmanTreeNode<int>(3);

    MH1->push(node1);
    MH1->push(node2);
    MH1->push(node3);
    HuffmanTreeNode<int> *root = nullptr;
    root = CreateHuffman(MH1);
    Preorder(root);
}
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template <typename T>
class MaxHeap
{
private:
    vector<T> MaxHeap; // 全局变量
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
        if (MaxHeap.size() <= 0)
        {
            throw out_of_range("the MaxHeap is empty");
        }
        return MaxHeap[0];
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
            if (i <= 0 || MaxHeap[i] < MaxHeap[p])
            {
                break;
            }
            swap(MaxHeap[i], MaxHeap[p]);
            i = p;
        }
    }

    void push(T data)
    {
        MaxHeap.push_back(data);
        siftUp(MaxHeap.size() - 1);
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
            if (l < MaxHeap.size() && MaxHeap[nxt] < MaxHeap[l])
                nxt = l;
            if (r < MaxHeap.size() && MaxHeap[nxt] < MaxHeap[r])
                nxt = r;
            if (i == nxt || (l >= MaxHeap.size() && r >= MaxHeap.size()))
            {
                break;
            }
            swap(MaxHeap[i], MaxHeap[nxt]);
            i = nxt;
        }
    }

    void pop()
    {
        if (MaxHeap.size() < 0)
        {
            throw out_of_range("the MaxHeap is empty.");
        }
        swap(MaxHeap[0], MaxHeap[MaxHeap.size() - 1]);
        MaxHeap.pop_back();
        siftDown(0);
    }
    // 向下堆化。
    void Down_Heapify(vector<T> nums)
    {
        MaxHeap = nums;
        for (int i = parent(MaxHeap.size() - 1); i >= 0; i--)
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
        for (int i = 0; i < MaxHeap.size(); i++)
        {
            cout << MaxHeap[i] << " ";
        }
        cout << endl;
    }
};

// driver code
int main()
{
    MaxHeap<int> *MH1 = new MaxHeap<int>();
    vector<int> v = {1, 3, 5, 2, 7, 9, 8, 10};
    MH1->Down_Heapify(v);
    MH1->Print();
    MaxHeap<int> *MH2 = new MaxHeap<int>();
    MH2->Insert_Heapify(v);
    MH2->Print();
}
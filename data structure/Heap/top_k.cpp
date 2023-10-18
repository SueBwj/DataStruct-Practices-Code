#include <queue>
#include <vector>
#include <iostream>
using namespace std;

priority_queue<int, vector<int>, greater<int>> Top_KHeap(vector<int> &nums, int k)
{
    priority_queue<int, vector<int>, greater<int>> MinHeap;
    for (int i = 0; i < k; i++)
    {
        MinHeap.push(nums[i]);
    }
    for (int i = k; i < nums.size(); i++)
    {
        if (nums[i] > MinHeap.top())
        {
            MinHeap.pop();
            MinHeap.push(nums[i]);
        }
    }
    return MinHeap;
}

// driver code
int main()
{
    vector<int> nums = {2, 3, 4, 5, 9, 273, 34, 23, 454, 234};
    priority_queue<int, vector<int>, greater<int>> MinHeap = Top_KHeap(nums, 4);
    while (!MinHeap.empty())
    {
        cout << MinHeap.top() << " ";
        MinHeap.pop();
    }
}
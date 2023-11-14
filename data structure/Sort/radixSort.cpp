#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define MaxSize 10 // 表示桶的大小

/* 获取元素 num 的第 k 位，其中 exp = 10^(k-1) */
int digit(int num, int exp)
{
    // 传入 exp 而非 k 可以避免在此重复执行昂贵的次方计算
    return (num / exp) % 10;
}

void countingSortDigit(vector<int> &nums, int exp)
{
    vector<int> counter(MaxSize, 0);
    for (int i = 0; i < nums.size(); i++)
    {
        // 获取对应位置的数字
        int d = digit(nums[i], exp);
        counter[d]++; // 统计出现的次数
    }
    // 求前缀和，转化为下标索引
    for (int i = 1; i < MaxSize; i++)
    {
        counter[i] += counter[i - 1];
    }
    vector<int> res(nums.size(), 0);
    for (int i = nums.size() - 1; i >= 0; i--)
    {
        int d = digit(nums[i], exp);
        int idx = counter[d] - 1;
        res[idx] = nums[i];
        counter[d]--;
    }
    // 使用结果覆盖原数组nums
    for (int i = 0; i < nums.size(); i++)
    {
        nums[i] = res[i];
    }
}

void radixSort(vector<int> &nums)
{
    // It returns a pointer to the largest
    int m = *max_element(nums.begin(), nums.end());
    for (int exp = 1; exp < m; exp *= 10)
    {
        countingSortDigit(nums, exp);
    }
}

void Print(const vector<int> &nums)
{
    for (auto num : nums)
    {
        cout << num << " ";
    }
    cout << endl;
}

int main()
{
    vector<int> nums = {22330110, 22330125, 22330040, 22330089, 22330010, 22330116, 22330152};
    radixSort(nums);
    Print(nums);
}

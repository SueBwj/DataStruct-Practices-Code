#include <iostream>
#include <vector>
using namespace std;

/*
计数排序适用于数据量大但数据范围较小的情况

计数排序只适用于非负整数。若想要将其用于其他类型的数据，需要确保这些数据可以被转换为非负整数，并且在转换过程中不能改变各个元素之间的相对大小关系。例如，对于包含负数的整数数组，可以先给所有数字加上一个常数，将全部数字转化为正数，排序完成后再转换回去即可。
*/

void countingSortNaive(vector<int> &nums)
{
    // 1. 找到最大值
    int m = 0;
    for (auto num : nums)
    {
        m = max(m, num);
    }
    // 2. 统计各数字出现的次数
    vector<int> counter(m + 1, 0);
    for (auto num : nums)
    {
        counter[num]++;
    }
    // 3. 遍历counter，将各元素填入原数组nums
    int i = 0;
    for (int j = 0; j < m + 1; j++)
    {
        for (int k = 0; k < counter[j]; k++)
        {
            nums[i++] = j;
        }
    }
}

void countingSort(vector<int> &nums)
{
    // 1. 找到最大值
    int m = 0;
    for (auto num : nums)
    {
        m = max(m, num);
    }
    // 2. 统计各数字出现的次数
    vector<int> counter(m + 1, 0);
    for (auto num : nums)
    {
        counter[num]++;
    }
    // 3. 求counter的前缀和，利用前缀和表示尾索引
    // 其实就是找到了每个元素对应的下标
    for (int i = 0; i < m; i++)
    {
        counter[i + 1] += counter[i];
    }
    // 4. 倒序遍历nums,将各元素填入结果数组res
    // 正序遍历 nums 也可以得到正确的排序结果，但结果是非稳定的。
    vector<int> res(nums.size());
    for (int i = nums.size() - 1; i >= 0; i--)
    {
        res[counter[nums[i]] - 1] = nums[i];
        counter[nums[i]]--;
    }
    nums = res;
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
    vector<int> nums = {2, 3, 4, 2, 2, 3, 1, 2, 4, 5, 3};
    countingSort(nums);
    Print(nums);
}
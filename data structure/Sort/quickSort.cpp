#include <iostream>
#include <vector>
using namespace std;

void swap(vector<int> &nums, int i, int j)
{
    int tmp = nums[i];
    nums[i] = nums[j];
    nums[j] = tmp;
}

/* 选取3个元素的中位数 */
int medianThree(const vector<int> &nums, int left, int mid, int right)
{
    // 使用异或运算来简化代码
    if ((nums[left] < nums[mid]) ^ (nums[left] < nums[right]))
    {
        return left;
    }
    else if ((nums[mid] < nums[left]) ^ (nums[mid] < nums[right]))
    {
        return mid;
    }
    else
    {
        return right;
    }
}

/* 哨兵划分(三数取中值) */
int partition(vector<int> &nums, int left, int right)
{
    int med = medianThree(nums, left, (left + right) / 2, right);
    swap(nums, med, left);
    int i = left, j = right;
    while (i < j)
    {
        // 从右往左找到首个小于pivot的值
        while (i < j && nums[j] >= nums[left])
        {
            j--;
        }
        // 从左往右找到首个大于pivot的值
        while (i < j && nums[i] <= nums[left])
        {
            i++;
        }
        swap(nums, i, j);
    }
    swap(nums, left, i);
    return i;
}

void quickSort(vector<int> &nums, int left, int right)
{
    if (left >= right)
    {
        return;
    }
    int pivot = partition(nums, left, right);
    quickSort(nums, left, pivot - 1);
    quickSort(nums, pivot + 1, right);
}

/* 快速排序（尾递归优化） */
void quickSort_better(vector<int> &nums, int left, int right)
{
    // 子数组长度为 1 时终止
    while (left < right)
    {
        // 哨兵划分操作
        int pivot = partition(nums, left, right);
        // 对两个子数组中较短的那个执行快排
        if (pivot - left < right - pivot)
        {
            quickSort(nums, left, pivot - 1); // 递归排序左子数组
            left = pivot + 1;                 // 剩余未排序区间为 [pivot + 1, right]
        }
        else
        {
            quickSort(nums, pivot + 1, right); // 递归排序右子数组
            right = pivot - 1;                 // 剩余未排序区间为 [left, pivot - 1]
        }
    }
}

void Print(vector<int> &nums)
{
    for (int i = 0; i < nums.size(); i++)
    {
        cout << nums[i] << ' ';
    }
    cout << endl;
}

int main()
{
    vector<int> nums = {4, 3, 2, 1, 6, 7, 8, 9, 5};
    quickSort(nums, 0, nums.size() - 1);
    Print(nums);
}

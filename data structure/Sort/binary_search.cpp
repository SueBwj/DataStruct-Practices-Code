#include <iostream>
#include <vector>
using namespace std;

int binarySearch(int num, const vector<int> &arr, int right, int left)
{
    int mid = (right + left) / 2;
    if (left > right)
    {
        return -1;
    }
    if (arr[mid] == num)
    {
        return mid;
    }
    else if (arr[mid] < num)
    {
        return binarySearch(num, arr, right, mid + 1);
    }
    else
    {
        return binarySearch(num, arr, mid - 1, left);
    }
}

// O(NlogN)
bool findSum(const vector<int> &arr, int x)
{
    for (int i = 0; i < arr.size(); i++)
    {
        if (binarySearch(x - arr[i], arr, arr.size(), 0) != -1)
        {
            cout << "i = " << i << endl;
            return true;
        }
    }
    return false;
}

// O(N)
bool findSumFaster(const vector<int> &arr, int x)
{
    int left = 0;
    int right = arr.size() - 1;
    while (left <= right)
    {
        if (arr[left] + arr[right] == x)
        {
            return true;
        }
        else if (arr[left] + arr[right] < x)
        {
            left++;
        }
        else
        {
            right--;
        }
    }
    return false;
}

// driver code
int main()
{
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 12, 15, 27, 54};
    if (findSumFaster(arr, 61))
    {
        cout << "true" << endl;
    }
    else
    {
        cout << "false" << endl;
    }
}
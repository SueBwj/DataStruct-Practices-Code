#include <iostream>
#include <cmath>
#define MAXTABLESIZE 100000 // 定义允许开辟的最大散列表长度
using namespace std;
/* Task
 *   1. 哈希表存值单元结构
 *   2. 哈希表整体结构
 *   3. 创建hash表
 *   4. 平方探测查找
 *   5. 线性探测查找
 *   6. 插入
 *   7. 哈希函数
 */

// 表示单元存储结构状态
typedef enum
{ // 分别对应：有合法元素、空、有已删除元素
    Legitimate,
    Empty,
    Deleted
} EntryType; // 定义单元状态类型

// 单元存储结构要存取数据和状态
struct HashEntry
{
    int data;
    EntryType info;
};

// 哈希表需要有数组和数组大小
struct HashTable
{
    HashEntry *arr;
    int TableSize;
};

// 判断素数
bool isPrime(int val)
{
    for (int i = (int)sqrt(val); i > 2; i--)
    {
        if (val % i == 0)
        {
            return false;
        }
    }
    return true;
}

// 查找素数
int nextPrime(int val)
{
    val = (val % 2 == 0) ? val + 1 : val + 2; // 从奇数开始查找
    while (val < MAXTABLESIZE)
    {
        if (isPrime(val))
        {
            return val;
        }
        val += 2;
    }
}

HashTable *CreateHashTable(int tableSize)
{
    HashTable *H = new HashTable();
    H->TableSize = nextPrime(tableSize);
    H->arr = new HashEntry[H->TableSize];
    for (int i = 0; i < H->TableSize; i++)
    {
        H->arr[i].info = Empty;
    }
}
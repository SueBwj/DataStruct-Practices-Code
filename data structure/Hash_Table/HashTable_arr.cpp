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
            cout << "val= " << val << endl;
            return val;
        }
        val += 2;
    }
    cout << "查找素数错误" << endl;
    return -1;
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
    return H;
}

// 对hash表的大小取余
int Hash(HashTable *H, int key)
{
    return key % H->TableSize;
}

// 线性探测法
int LinearSearch(HashTable *H, int key)
{
    int newPos, currentPos;
    newPos = currentPos = Hash(H, key);
    while (H->arr[newPos].info != Empty && H->arr[newPos].data != key)
    {
        newPos = (newPos + 1) % H->TableSize;
    }
    return newPos;
}

// 平方探测法
int SquareSearch(HashTable *H, int key)
{
    int currentPos, newPos;
    int cnt = 0; // 记录冲突次数
    newPos = currentPos = Hash(H, key);
    while (H->arr[newPos].info != Empty && H->arr[newPos].data != key)
    {
        ++cnt;
        if (cnt % 2 != 0)
        {
            // 产生奇数次冲突
            newPos = (int)(currentPos + pow(((cnt + 1) / 2), 2)) % H->TableSize;
        }
        else
        { // 产生偶数次冲突
            newPos = (int)(currentPos - pow((cnt / 2), 2));
            while (newPos < 0)
            {
                newPos += H->TableSize;
            }
        }
    }
    return newPos;
}

void Insert(HashTable *H, int key)
{
    int addr = Hash(H, key);
    addr = SquareSearch(H, key);
    if (H->arr[addr].info != Legitimate)
    {
        H->arr[addr].data = key;
        H->arr[addr].info = Legitimate;
    }
}

void Print(HashTable *H)
{
    for (int i = 0; i < H->TableSize; i++)
    {
        cout << H->arr[i].data << " ";
    }
    cout << endl;
}

int main()
{
    HashTable *H = nullptr;
    H = CreateHashTable(10);
    Insert(H, 47);
    Insert(H, 7);
    Insert(H, 29);
    Insert(H, 11);
    Insert(H, 9);
    Insert(H, 84);
    Insert(H, 54);
    Insert(H, 20);
    Insert(H, 30);
    Print(H);
}

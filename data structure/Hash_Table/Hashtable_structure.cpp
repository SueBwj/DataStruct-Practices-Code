#include <iostream>
using namespace std;
#define HASHSIZE 13;
#define NULLKEY -32768 // 表示当前地址没有元素
int m = HASHSIZE;      // 全局变量

struct HashTable
{
    int cnt;  // 当前元素个数
    int size; // hashtable的大小
    int *arr; // 动态分配数组
};

void InitHashTable(HashTable *H)
{
    H->size = HASHSIZE;
    H->arr = (int *)malloc(sizeof(int) * H->size);
    for (int i = 0; i < H->size; i++)
    {
        H->arr[i] = NULLKEY;
    }
}

// 散列函数 -- 根据key得出其插入的地址
int Hash(int key)
{
    return key % m;
}

// 插入关键字进散列表
void InsertHashTable(HashTable *H, int key)
{
    int addr = Hash(key);
    while (H->arr[addr] != NULLKEY)
    {
        addr = (addr + 1) % m; // 开放地址的线性探测
        if (addr == Hash(key))
        {
            cout << "散列表已经满了" << endl;
        }
    }
    H->arr[addr] = key;
}

bool SearchHash(HashTable *H, int key)
{
    int addr = Hash(key); // 获取key的地址
    // 产生了冲突
    while (H->arr[addr] != key)
    {
        if (H->arr[addr] == NULLKEY || addr == Hash(key))
        {
            cout << "该关键词不存在" << endl;
            return false;
        }
        addr = (addr + 1) % m;
    }
    return true;
}

// driver code
int main()
{
    HashTable *H = new HashTable();
    InitHashTable(H);
    InsertHashTable(H, 2);
    InsertHashTable(H, 22);
    InsertHashTable(H, 12);
    for (int i = 0; i < H->size; i++)
    {
        cout << H->arr[i] << " ";
    }
    return 0;
}
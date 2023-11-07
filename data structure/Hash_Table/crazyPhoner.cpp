#include <iostream>
#include <string>
#include <cmath>
#define MAXSIZE 100000
using namespace std;

struct HashNode
{
    string phoneNumber;
    HashNode *next;
    int cnt; // 统计出现的次数
    HashNode() : next(nullptr), cnt(0) {}
    HashNode(string phone) : phoneNumber(phone), next(nullptr), cnt(1) {}
};

struct HashTable
{
    HashNode *arr;
    int size; // 哈希表的大小
};
typedef HashTable *HashTbl;

int nextPrime(int n)
{
    int i;
    int p = (n % 2) == 0 ? n + 1 : n + 2; // 从大于N的下一个奇数开始
    while (p <= MAXSIZE)
    {
        for (i = sqrt(p); i > 2; i--)
        {
            if (p % i == 0)
            {
                break; // p不是素数
            }
        }
        if (i == 2)
        {
            break; // 正常结束循环
        }
        else
        {
            p += 2; // 继续判断下一个奇数
        }
    }
    return p;
}
int HashCode(string phone, int size)
{
    return (atoi(phone.substr(6, 5).c_str())) % size;
}

void InitHashTbl(HashTbl H, int size)
{
    H->arr = new HashNode[size];
    H->size = size;
}

// 如果找到了就返回这个node，没有找到就返回nullptr
HashNode *HashFind(HashTbl H, string phone)
{
    int addr = HashCode(phone, H->size);
    HashNode *tmp = H->arr[addr].next;
    while (tmp && tmp->phoneNumber != phone)
    {
        tmp = tmp->next;
    }
    return tmp;
}

void HashInsert(HashTbl H, string phone)
{
    HashNode *tmp = HashFind(H, phone);
    if (tmp != nullptr)
    {
        tmp->cnt += 1;
    }
    else
    {
        // 插入的时候插入到链表头而不是链表尾部
        HashNode *node = new HashNode(phone);
        int addr = HashCode(phone, H->size);
        HashNode *headNext = H->arr[addr].next;
        node->next = headNext;
        H->arr[addr].next = node;
    }
}

void ScanAndOutput(HashTbl H)
{
    HashNode *p = nullptr;
    int MaxCnt = 0;
    string PhoneNumber;
    int Pcnt = 0; // 并列人数
    for (int i = 0; i < H->size; i++)
    {
        p = H->arr[i].next;
        while (p)
        {
            if (MaxCnt < p->cnt)
            {
                MaxCnt = p->cnt;
                PhoneNumber = p->phoneNumber;
                Pcnt = 1;
            }
            else if (MaxCnt == p->cnt)
            {
                if (p->phoneNumber < PhoneNumber)
                {
                    PhoneNumber = p->phoneNumber;
                }
                Pcnt += 1;
            }
            p = p->next;
        }
    }
    cout << PhoneNumber << " " << MaxCnt;
    if (Pcnt > 1)
    {
        cout << " " << Pcnt;
    }
}

int main()
{
    int N;
    cin >> N;
    HashTbl H = new HashTable();
    InitHashTbl(H, nextPrime(2 * N));
    int tmp = 2 * N;
    while (tmp)
    {
        string phone;
        cin >> phone;
        HashInsert(H, phone);
        tmp--;
    }
    ScanAndOutput(H);
}
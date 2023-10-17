#include <iostream>
using namespace std;
#define HASHSIZE 13;
#define NULLKEY -32768 // ��ʾ��ǰ��ַû��Ԫ��
int m = HASHSIZE;      // ȫ�ֱ���

struct HashTable
{
    int cnt;  // ��ǰԪ�ظ���
    int size; // hashtable�Ĵ�С
    int *arr; // ��̬��������
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

// ɢ�к��� -- ����key�ó������ĵ�ַ
int Hash(int key)
{
    return key % m;
}

// ����ؼ��ֽ�ɢ�б�
void InsertHashTable(HashTable *H, int key)
{
    int addr = Hash(key);
    while (H->arr[addr] != NULLKEY)
    {
        addr = (addr + 1) % m; // ���ŵ�ַ������̽��
        if (addr == Hash(key))
        {
            cout << "ɢ�б��Ѿ�����" << endl;
        }
    }
    H->arr[addr] = key;
}

bool SearchHash(HashTable *H, int key)
{
    int addr = Hash(key); // ��ȡkey�ĵ�ַ
    // �����˳�ͻ
    while (H->arr[addr] != key)
    {
        if (H->arr[addr] == NULLKEY || addr == Hash(key))
        {
            cout << "�ùؼ��ʲ�����" << endl;
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
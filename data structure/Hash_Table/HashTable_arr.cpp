#include <iostream>
#include <cmath>
#define MAXTABLESIZE 100000 // ���������ٵ����ɢ�б���
using namespace std;
/* Task
 *   1. ��ϣ���ֵ��Ԫ�ṹ
 *   2. ��ϣ������ṹ
 *   3. ����hash��
 *   4. ƽ��̽�����
 *   5. ����̽�����
 *   6. ����
 *   7. ��ϣ����
 */

// ��ʾ��Ԫ�洢�ṹ״̬
typedef enum
{ // �ֱ��Ӧ���кϷ�Ԫ�ء��ա�����ɾ��Ԫ��
    Legitimate,
    Empty,
    Deleted
} EntryType; // ���嵥Ԫ״̬����

// ��Ԫ�洢�ṹҪ��ȡ���ݺ�״̬
struct HashEntry
{
    int data;
    EntryType info;
};

// ��ϣ����Ҫ������������С
struct HashTable
{
    HashEntry *arr;
    int TableSize;
};

// �ж�����
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

// ��������
int nextPrime(int val)
{
    val = (val % 2 == 0) ? val + 1 : val + 2; // ��������ʼ����
    while (val < MAXTABLESIZE)
    {
        if (isPrime(val))
        {
            cout << "val= " << val << endl;
            return val;
        }
        val += 2;
    }
    cout << "������������" << endl;
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

// ��hash��Ĵ�Сȡ��
int Hash(HashTable *H, int key)
{
    return key % H->TableSize;
}

// ����̽�ⷨ
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

// ƽ��̽�ⷨ
int SquareSearch(HashTable *H, int key)
{
    int currentPos, newPos;
    int cnt = 0; // ��¼��ͻ����
    newPos = currentPos = Hash(H, key);
    while (H->arr[newPos].info != Empty && H->arr[newPos].data != key)
    {
        ++cnt;
        if (cnt % 2 != 0)
        {
            // ���������γ�ͻ
            newPos = (int)(currentPos + pow(((cnt + 1) / 2), 2)) % H->TableSize;
        }
        else
        { // ����ż���γ�ͻ
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
    addr = LinearSearch(H, key);
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

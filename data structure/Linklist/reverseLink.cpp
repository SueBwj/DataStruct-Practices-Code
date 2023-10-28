#include <iostream>
using namespace std;

typedef struct Node
{
    int data;
    Node *next;
    Node() : data(0), next(nullptr) {}
    Node(int data) : data(data), next(nullptr) {}
    Node(int data, Node *node) : data(data), next(node) {}
} Node;
typedef Node *link;

void Print_List(link l)
{
    if (l == nullptr)
    {
        return;
    }
    else
    {
        cout << l->data << " ";
        Print_List(l->next);
    }
}

link Reverse(link l, int k)
{
    int cnt = 0;
    link new_node = l->next;
    link old_node = l->next;
    link tmp = old_node->next;
    while (cnt < k)
    {
        old_node->next = new_node;
        new_node = old_node;
        old_node = tmp;
        tmp = old_node->next;
        cnt++;
    }
    l->next->next = old_node;
    return new_node;
}

int main()
{
    link l = new Node(0);
    l->next = new Node(1);
    l->next->next = new Node(2);
    l->next->next->next = new Node(3);
    l->next->next->next->next = new Node(4);
    l->next->next->next->next->next = new Node(5);
    l->next->next->next->next->next->next = new Node(6);
    Print_List(l->next);
    cout << endl;
    l->next = Reverse(l, 5);
    Print_List(l->next);
}
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

typedef struct Node *Linklist;

Linklist Merge(Linklist l1, Linklist l2)
{
    if (l1 == nullptr)
    {
        return l2;
    }
    else if (l2 == nullptr)
    {
        return l1;
    }
    else
    {
        if (l1->data <= l2->data)
        {
            Linklist l = new Node(l1->data);
            l->next = Merge(l1->next, l2);
            return l;
        }
        else
        {
            Linklist l = new Node(l2->data);
            l->next = Merge(l1, l2->next);
            return l;
        }
    }
}

void Print_List(Linklist l)
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

int main()
{
    Linklist head1 = new Node(1);
    head1->next = new Node(2);
    head1->next->next = new Node(3);
    head1->next->next->next = new Node(5);

    Linklist head2 = new Node(2);
    head2->next = new Node(6);
    head2->next->next = new Node(9);

    Linklist l = Merge(head1, head2);
    Print_List(l);
    return 0;
}
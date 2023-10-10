#include <iostream>
using namespace std;
typedef bool (*FucntionPointer)(int);

typedef struct Node
{
    int data;
    Node *next;
    Node() : data(0), next(nullptr) {}
    Node(int data) : data(data), next(nullptr) {}
    Node(int data, Node *node) : data(data), next(node) {}
} Node;

typedef struct Node *Linklist;

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

bool is_even(int x)
{
    return x % 2 == 0;
}

bool is_odd(int x)
{
    return x % 2 == 1;
}

Linklist filter_lst(Linklist l, FucntionPointer f)
{
    Linklist new_lst;
    if (l == nullptr)
    {
        return nullptr;
    }
    else
    {
        if (f(l->data))
        {
            new_lst = new Node(l->data);
            new_lst->next = filter_lst(l->next, f);
        }
        else
        {
            new_lst = filter_lst(l->next, f);
        }
        return new_lst;
    }
}

int main()
{
    Linklist head1 = new Node(1);
    head1->next = new Node(2);
    head1->next->next = new Node(3);
    head1->next->next->next = new Node(5);
    head1->next->next->next->next = new Node(2);

    Linklist l = filter_lst(head1, is_odd);
    Print_List(l);
}

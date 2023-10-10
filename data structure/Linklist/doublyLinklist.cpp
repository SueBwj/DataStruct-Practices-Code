#include <iostream>
using namespace std;

typedef struct DoubleLink
{
    int data;
    DoubleLink *prev;
    DoubleLink *next;
} DBNode, *DBNodePtr;

void Insert(DBNodePtr p, int x)
{
    DBNodePtr node = new DBNode();
    node->data = x;
    node->next = p->next;
    p->next->prev = node;
    node->prev = p;
    p->next = node;
}

void Delete(DBNodePtr p)
{
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    // p->next = nullptr
    // p->prev = nullptr
}
#include <iostream>
#include <stack>
using namespace std;

// 用两个栈来实现队列
/*
 * 1. 栈1用来实现入队操作
 * 2. 当要出队时，将栈1全部放入栈2
 */

typedef struct Queue
{
    stack<int> st1;
    stack<int> st2;
} Queue;

void enqueue(Queue *q, int x)
{
    q->st1.push(x);
}

int dequeue(Queue *q)
{
    while (!q->st1.empty())
    {
        int tmp = q->st1.top();
        q->st2.push(tmp);
        q->st1.pop();
    }
    int front = q->st2.top();
    q->st2.pop();
    return front;
}

// driver code
int main()
{
    Queue *q = new Queue();
    enqueue(q, 1);
    enqueue(q, 2);
    enqueue(q, 3);
    enqueue(q, 4);
    enqueue(q, 5);
    enqueue(q, 6);
    cout << dequeue(q) << " ";
    cout << dequeue(q) << " ";
    cout << dequeue(q) << " ";
    cout << dequeue(q) << " ";
    cout << dequeue(q) << " ";
}
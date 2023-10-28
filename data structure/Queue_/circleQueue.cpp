#include <iostream>
using namespace std;

struct QNode
{
    int *Data;
    int rear;
    int front;
    int size;
};
typedef struct QNode *Queue;

void createQueue(Queue q, int s)
{
    q->Data = new int[s];
    q->rear = q->front = 0;
    q->size = s;
}

int QueueLength(Queue q)
{
    return (q->rear - q->front + q->size) % q->size;
}

bool isFull(Queue q)
{
    return (q->rear + 1) % q->size == q->front;
}

bool isEmpty(Queue q)
{
    return q->front == q->rear;
}

int getHead(Queue q)
{
    if (!isEmpty(q))
        return q->Data[q->front];
    return -1;
}

void enQueue(Queue q, int x)
{
    q->Data[q->rear] = x;
    q->rear = (q->rear + 1) % q->size;
    cout << q->rear << " " << QueueLength(q) << endl;
}

void deQueue(Queue q)
{
    if (!isEmpty(q))
    {
        q->front = (q->front + 1) % q->size;
    }
    cout << q->front << " " << QueueLength(q) << endl;
}

int main()
{
    int s, n;
    cin >> s >> n;
    Queue q = new QNode();
    createQueue(q, s);
    while (n > 0)
    {
        int num;
        cin >> num;
        switch (num)
        {
        case 0:
            int x;
            cin >> x;
            enQueue(q, x);
            break;
        case 1:
            deQueue(q);
            break;
        default:
            break;
        }
        n--;
    }
}
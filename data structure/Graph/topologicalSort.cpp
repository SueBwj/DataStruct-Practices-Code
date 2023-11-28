#include <iostream>
#include <stack>
#define MAXVEX 100
using namespace std;

typedef struct EdgeNode
{
    int adjvex;
    int weight;
    struct EdgeNode *next;
} EdgeNode;
typedef struct VertexNode
{
    int in; // ���
    int data;
    EdgeNode *firstedge;
} VertexNode, AdjList[MAXVEX];

typedef struct
{
    AdjList adjList;
    int numVertexes, numEdges;
} graphAdjList, *GraphAdjList;

void CreateALGraph(GraphAdjList G)
{
    int i, j, k;
    EdgeNode *e;
    cout << "���붥��ͱ���" << endl;
    cin >> G->numVertexes >> G->numEdges;
    for (i = 0; i < G->numVertexes; i++)
    {
        cin >> G->adjList[i].data;
        G->adjList[i].firstedge = nullptr;
    }
    for (k = 0; k < G->numEdges; k++)
    {
        cout << "�����(vi,vj)�ϵĶ������" << endl;
        cin >> i >> j;
        e = new EdgeNode();
        e->adjvex = j;
        G->adjList[j].in++;
        e->next = G->adjList[i].firstedge;
        G->adjList[i].firstedge = e;
    }
}

void TopologicalSort(GraphAdjList GL)
{
    EdgeNode *e;
    int i, k, gettop;
    int count = 0;
    stack<int> st; // �洢���Ϊ0�Ķ���
    for (i = 0; i < GL->numVertexes; i++)
    {
        if (GL->adjList[i].in == 0)
        {
            st.push(i); // �����Ϊ0�Ķ�����ջ
        }
    }
    while (!st.empty())
    {
        gettop = st.top();
        st.pop();
        cout << gettop << "->";
        count++; // ͳ�����������
        for (e = GL->adjList[gettop].firstedge; e; e = e->next)
        {
            k = e->adjvex;
            if (!(--GL->adjList[k].in))
            {
                // ���k�Ŷ����ȥ��Ⱥ��Ϊ1��������������ջ��
                st.push(k);
            }
        }
    }
    if (count < GL->numVertexes)
    {
        cout << "���ڻ�" << endl;
    }
    else
    {
        cout << "�����ڻ�" << endl;
    }
}

int main()
{
    GraphAdjList G = new graphAdjList();
    CreateALGraph(G);
    TopologicalSort(G);
}
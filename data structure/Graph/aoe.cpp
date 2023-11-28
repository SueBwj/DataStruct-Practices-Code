#include <iostream>
#include <stack>
#define MAXVEX 100
using namespace std;
int *etv, *ltv; // �¼����緢��ʱ�����ٷ���ʱ������
stack<int> st2; // �����洢�������е�ջ

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
        e = new EdgeNode();
        cout << "�����(vi,vj)�ϵĶ�����ź�Ȩ��" << endl;
        cin >> i >> j >> e->weight;
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

    etv = new int[GL->numVertexes];
    for (i = 0; i < GL->numVertexes; i++)
    {
        etv[i] = 0; // ��ʼ��Ϊ0
    }

    while (!st.empty())
    {
        gettop = st.top();
        st2.push(gettop); // �������Ķ������ѹ���������е�ջ
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
            // �������ʱ�����緢��ʱ��ֵ
            if (etv[gettop] + e->weight > etv[k])
            {
                etv[k] = etv[gettop] + e->weight;
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

void CriticalPath(GraphAdjList GL)
{
    EdgeNode *e;
    int i, gettop, k, j;
    int ete, lte; // ��������緢��ʱ�����ٷ���ʱ�����
    TopologicalSort(GL);
    ltv = new int[GL->numVertexes];
    for (i = 0; i < GL->numVertexes; i++)
    {
        ltv[i] = etv[GL->numVertexes - 1]; // ��ʼ��ltv
    }
    while (!st2.empty())
    {
        gettop = st2.top();
        st2.pop();
        for (e = GL->adjList[gettop].firstedge; e; e = e->next)
        {
            k = e->adjvex;
            // ��һ���¼������緢��ʱ��-weight������һ���¼����������¼�
            if (ltv[k] - e->weight < ltv[gettop])
            {
                // �������������ʱ��
                ltv[gettop] = ltv[k] - e->weight;
            }
        }
    }
    for (j = 0; j < GL->numVertexes; j++)
    {
        for (e = GL->adjList[j].firstedge; e; e = e->next)
        {
            k = e->adjvex;
            ete = etv[j];
            lte = ltv[k] - e->weight;
            if (ete == lte)
            {
                cout << '<' << 'v' << j << ",v" << k << '>' << " length: " << e->weight << endl;
            }
        }
    }
}

int main()
{
    GraphAdjList G = new graphAdjList();
    CreateALGraph(G);
    CriticalPath(G);
}
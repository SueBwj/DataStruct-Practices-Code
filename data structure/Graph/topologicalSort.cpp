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
    int in; // 入度
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
    cout << "输入顶点和边数" << endl;
    cin >> G->numVertexes >> G->numEdges;
    for (i = 0; i < G->numVertexes; i++)
    {
        cin >> G->adjList[i].data;
        G->adjList[i].firstedge = nullptr;
    }
    for (k = 0; k < G->numEdges; k++)
    {
        cout << "输入边(vi,vj)上的顶点序号" << endl;
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
    stack<int> st; // 存储入度为0的顶点
    for (i = 0; i < GL->numVertexes; i++)
    {
        if (GL->adjList[i].in == 0)
        {
            st.push(i); // 将入度为0的顶点入栈
        }
    }
    while (!st.empty())
    {
        gettop = st.top();
        st.pop();
        cout << gettop << "->";
        count++; // 统计输出顶点数
        for (e = GL->adjList[gettop].firstedge; e; e = e->next)
        {
            k = e->adjvex;
            if (!(--GL->adjList[k].in))
            {
                // 如果k号顶点减去入度后变为1，则将这个顶点加入栈中
                st.push(k);
            }
        }
    }
    if (count < GL->numVertexes)
    {
        cout << "存在环" << endl;
    }
    else
    {
        cout << "不存在环" << endl;
    }
}

int main()
{
    GraphAdjList G = new graphAdjList();
    CreateALGraph(G);
    TopologicalSort(G);
}
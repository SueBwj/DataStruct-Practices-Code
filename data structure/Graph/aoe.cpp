#include <iostream>
#include <stack>
#define MAXVEX 100
using namespace std;
int *etv, *ltv; // 事件最早发生时间和最迟发生时间数组
stack<int> st2; // 用来存储拓扑序列的栈

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
        e = new EdgeNode();
        cout << "输入边(vi,vj)上的顶点序号和权重" << endl;
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
    stack<int> st; // 存储入度为0的顶点
    for (i = 0; i < GL->numVertexes; i++)
    {
        if (GL->adjList[i].in == 0)
        {
            st.push(i); // 将入度为0的顶点入栈
        }
    }

    etv = new int[GL->numVertexes];
    for (i = 0; i < GL->numVertexes; i++)
    {
        etv[i] = 0; // 初始化为0
    }

    while (!st.empty())
    {
        gettop = st.top();
        st2.push(gettop); // 将弹出的顶点序号压入拓扑序列的栈
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
            // 求各顶点时间最早发生时间值
            if (etv[gettop] + e->weight > etv[k])
            {
                etv[k] = etv[gettop] + e->weight;
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

void CriticalPath(GraphAdjList GL)
{
    EdgeNode *e;
    int i, gettop, k, j;
    int ete, lte; // 声明活动最早发生时间和最迟发生时间变量
    TopologicalSort(GL);
    ltv = new int[GL->numVertexes];
    for (i = 0; i < GL->numVertexes; i++)
    {
        ltv[i] = etv[GL->numVertexes - 1]; // 初始化ltv
    }
    while (!st2.empty())
    {
        gettop = st2.top();
        st2.pop();
        for (e = GL->adjList[gettop].firstedge; e; e = e->next)
        {
            k = e->adjvex;
            // 下一个事件的最早发生时间-weight就是上一个事件的最晚发生事件
            if (ltv[k] - e->weight < ltv[gettop])
            {
                // 求各顶点最晚发生时间
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
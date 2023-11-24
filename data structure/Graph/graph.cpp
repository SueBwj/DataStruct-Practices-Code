#include <iostream>
using namespace std;

/*邻接矩阵的存储结构*/
typedef char VertexType;
typedef int EdgeType;

#define MAXVEX 100
#define INFINITY 65535

typedef struct
{
    VertexType vexs[MAXVEX];
    EdgeType arc[MAXVEX][MAXVEX];
    int numVertexes, numEdges; // 存储当前顶点数量和边数
} MGraph;

/*邻接表的存储结构*/

typedef struct EdgeNode
{
    int adjvex;            // 存储该顶点对应的下标
    EdgeType weight;       // 存储边的权重
    struct EdgeNode *next; // 指向下一个邻接点
} EdgeNode;

typedef struct VertexNode
{
    VertexType data;     // 存储顶点信息
    EdgeNode *firstedge; // 边表头指针
} VertexNode, AdjList[MAXVEX];

typedef struct
{
    AdjList ajdList;
    int numVertexes, numEdges; // 存储当前顶点数量和边数
} GraphAdjList;

/*建立无向图的邻接矩阵表示*/
void CreateMGraph(MGraph *G)
{
    int i, j, k, w;
    cout << "请输入顶点数和边数:" << endl;
    cin >> G->numVertexes >> G->numEdges;
    cout << "输入顶点信息" << endl;
    for (i = 0; i < G->numVertexes; i++)
    {
        cin >> G->vexs[i];
    }
    // 邻接矩阵初始化
    for (i = 0; i < G->numVertexes; i++)
    {
        for (j = 0; j < G->numVertexes; j++)
        {
            G->arc[i][j] = INFINITY;
        }
    }
    for (k = 0; k < G->numEdges; k++)
    {
        cout << "输入下标i,j和权w" << endl;
        cin >> i >> j >> G->arc[i][j];
        G->arc[j][i] = G->arc[i][j];
    }
}

/*Prim算法生成最小生成树*/
void MiniSpanTree_Prim(MGraph G)
{
    int min, i, j, k;
    int adjvex[MAXVEX];  // 保存相关顶点下标
    int lowcost[MAXVEX]; // 保存相关顶点间边的权值
    lowcost[0] = 0;      // 初始化第一个权值为0, 即v0加入生成树
    adjvex[0] = 0;       // 初始化第一个顶点下标为0
    for (i = 1; i < G.numVertexes; i++)
    {
        lowcost[i] = G.arc[0][i];
        adjvex[i] = 0;
    }
    for (i = 1; i < G.numVertexes; i++)
    {
        min = INFINITY; // 初始化权值最小为正无穷
        j = 1, k = 0;
        // 找出当前权值最小的边
        while (j < G.numVertexes)
        {
            if (lowcost[j] != 0 && lowcost[j] < min)
            {
                min = lowcost[j];
                k = j;
            }
            j++;
        }
        cout << '(' << adjvex[k] << ',' << k << ')' << endl;
        lowcost[k] = 0; // 将当前顶点权值设置为0,表示此顶点已经完成任务
        // 把找到的顶点的边的权值加入到lowcost中
        for (j = 1; j < G.numVertexes; j++)
        {
            if (lowcost[j] != 0 && G.arc[k][j] < lowcost[j])
            {
                lowcost[j] = G.arc[k][j];
                adjvex[j] = k; // 将下标为k的顶点加入到adjvex中，相当于记录该条边的父顶点是什么
            }
        }
    }
}

int main()
{
    MGraph *G = new MGraph();
    CreateMGraph(G);
    MiniSpanTree_Prim(*G);
}
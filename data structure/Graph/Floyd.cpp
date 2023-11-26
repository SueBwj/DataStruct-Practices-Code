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

typedef int Pathmatrix[MAXVEX][MAXVEX];
typedef int ShortPathTable[MAXVEX][MAXVEX];

/*Floyd算法，求网图G中各顶点v到其余顶点w最短路径P[v][w]及带权长度D[v][w]*/
void ShortestPath_Floyd(MGraph G, Pathmatrix *P, ShortPathTable *D)
{
    int v, w, k;
    // 初始化D与P
    for (v = 0; v < G.numVertexes; ++v)
    {
        for (w = 0; w < G.numVertexes; ++w)
        {
            (*D)[v][w] = G.arc[v][w];
            (*P)[v][w] = w;
        }
    }
    for (k = 0; k < G.numVertexes; ++k)
    {
        for (v = 0; v < G.numVertexes; ++v)
        {
            for (w = 0; w < G.numVertexes; ++w)
            {
                if ((*D)[v][w] > (*D)[v][k] + (*D)[k][w])
                {
                    (*D)[v][w] = (*D)[v][k] + (*D)[k][w];
                    (*P)[v][w] = (*P)[v][k]; // 路径设置为经过下标为k的顶点
                }
            }
        }
    }
}

/*打印最短路径*/
void printShortestPath(MGraph G, ShortPathTable *P)
{
    int v, w, k;
    for (v = 0; v < G.numVertexes; v++)
    {
        for (w = v + 1; w < G.numVertexes; w++)
        {
            k = (*P)[v][w];
            cout << "path: " << v;
            while (k != w)
            {
                cout << " -> " << k;
                k = (*P)[k][w];
            }
            cout << " -> " << w << endl;
        }
    }
}
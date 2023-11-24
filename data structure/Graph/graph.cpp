#include <iostream>
using namespace std;

/*�ڽӾ���Ĵ洢�ṹ*/
typedef char VertexType;
typedef int EdgeType;

#define MAXVEX 100
#define INFINITY 65535

typedef struct
{
    VertexType vexs[MAXVEX];
    EdgeType arc[MAXVEX][MAXVEX];
    int numVertexes, numEdges; // �洢��ǰ���������ͱ���
} MGraph;

/*�ڽӱ�Ĵ洢�ṹ*/

typedef struct EdgeNode
{
    int adjvex;            // �洢�ö����Ӧ���±�
    EdgeType weight;       // �洢�ߵ�Ȩ��
    struct EdgeNode *next; // ָ����һ���ڽӵ�
} EdgeNode;

typedef struct VertexNode
{
    VertexType data;     // �洢������Ϣ
    EdgeNode *firstedge; // �߱�ͷָ��
} VertexNode, AdjList[MAXVEX];

typedef struct
{
    AdjList ajdList;
    int numVertexes, numEdges; // �洢��ǰ���������ͱ���
} GraphAdjList;

/*��������ͼ���ڽӾ����ʾ*/
void CreateMGraph(MGraph *G)
{
    int i, j, k, w;
    cout << "�����붥�����ͱ���:" << endl;
    cin >> G->numVertexes >> G->numEdges;
    cout << "���붥����Ϣ" << endl;
    for (i = 0; i < G->numVertexes; i++)
    {
        cin >> G->vexs[i];
    }
    // �ڽӾ����ʼ��
    for (i = 0; i < G->numVertexes; i++)
    {
        for (j = 0; j < G->numVertexes; j++)
        {
            G->arc[i][j] = INFINITY;
        }
    }
    for (k = 0; k < G->numEdges; k++)
    {
        cout << "�����±�i,j��Ȩw" << endl;
        cin >> i >> j >> G->arc[i][j];
        G->arc[j][i] = G->arc[i][j];
    }
}

/*Prim�㷨������С������*/
void MiniSpanTree_Prim(MGraph G)
{
    int min, i, j, k;
    int adjvex[MAXVEX];  // ������ض����±�
    int lowcost[MAXVEX]; // ������ض����ߵ�Ȩֵ
    lowcost[0] = 0;      // ��ʼ����һ��ȨֵΪ0, ��v0����������
    adjvex[0] = 0;       // ��ʼ����һ�������±�Ϊ0
    for (i = 1; i < G.numVertexes; i++)
    {
        lowcost[i] = G.arc[0][i];
        adjvex[i] = 0;
    }
    for (i = 1; i < G.numVertexes; i++)
    {
        min = INFINITY; // ��ʼ��Ȩֵ��СΪ������
        j = 1, k = 0;
        // �ҳ���ǰȨֵ��С�ı�
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
        lowcost[k] = 0; // ����ǰ����Ȩֵ����Ϊ0,��ʾ�˶����Ѿ��������
        // ���ҵ��Ķ���ıߵ�Ȩֵ���뵽lowcost��
        for (j = 1; j < G.numVertexes; j++)
        {
            if (lowcost[j] != 0 && G.arc[k][j] < lowcost[j])
            {
                lowcost[j] = G.arc[k][j];
                adjvex[j] = k; // ���±�Ϊk�Ķ�����뵽adjvex�У��൱�ڼ�¼�����ߵĸ�������ʲô
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
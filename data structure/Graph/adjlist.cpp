#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
struct Vertex
{
    int val;
    Vertex() = default;
    Vertex(int x) : val(x){};
};

class GraphAdjList
{
private:
    void printVector(const vector<Vertex *> &v)
    {
        for (auto x : v)
        {
            cout << x->val << ' ';
        }
        cout << endl;
    }

public:
    unordered_map<Vertex *, vector<Vertex *>> adjList;

    GraphAdjList(const vector<vector<Vertex *>> &edges)
    {
        for (const vector<Vertex *> &edge : edges)
        {
            addVertex(edge[0]);
            addVertex(edge[1]);
            addEdge(edge[0], edge[1]);
        }
    }

    /*在vector中删除指定节点*/
    void remove(vector<Vertex *> &vec, Vertex *vet)
    {
        for (int i = 0; i < vec.size(); i++)
        {
            if (vec[i] == vet)
            {
                vec.erase(vec.begin() + i);
                break;
            }
        }
    }

    /*获取节点数量*/
    int size()
    {
        return adjList.size();
    }

    /*添加边*/
    void addEdge(Vertex *vet1, Vertex *vet2)
    {
        if (!adjList.count(vet1) || !adjList.count(vet2) || vet1 == vet2)
        {
            throw invalid_argument("不存在顶点");
        }
        adjList[vet1].push_back(vet2);
        adjList[vet2].push_back(vet1);
    }

    /*删除边*/
    void deleteEdge(Vertex *vet1, Vertex *vet2)
    {
        if (!adjList.count(vet1) || !adjList.count(vet2) || vet1 == vet2)
        {
            throw invalid_argument("不存在顶点");
        }
        remove(adjList[vet1], vet2);
        remove(adjList[vet2], vet1);
    }
    /*添加顶点*/
    void addVertex(Vertex *vet)
    {
        if (adjList.count(vet))
        {
            return;
        }
        adjList[vet] = vector<Vertex *>();
    }

    /*删除顶点*/
    void deleteVertex(Vertex *vet)
    {
        if (!adjList.count(vet))
        {
            throw invalid_argument("不存在顶点");
        }
        adjList.erase(vet);
        // 删除与其他顶点有连接的边
        for (auto &adj : adjList)
        {
            remove(adj.second, vet);
        }
    }

    /* 打印邻接表 */
    void print()
    {
        cout << "邻接表 =" << endl;
        for (auto &adj : adjList)
        {
            const auto &key = adj.first;
            const auto &vec = adj.second;
            cout << key->val << ": ";
            printVector(vec);
        }
    }
};

// driver code
int main()
{
    Vertex *v1 = new Vertex(1);
    Vertex *v2 = new Vertex(2);
    Vertex *v3 = new Vertex(3);
    Vertex *v4 = new Vertex(4);

    vector<vector<Vertex *>> edges = {{v1, v2},
                                      {v2, v4},
                                      {v1, v3},
                                      {v3, v4}};
    GraphAdjList *adjlist = new GraphAdjList(edges);
    adjlist->print();
}
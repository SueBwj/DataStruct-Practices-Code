/*基于邻接矩阵的实现*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class GraphAdjMat
{
private:
    vector<int> vertices;
    vector<vector<int>> adjMat;

    bool boundaryCheck(int i, int j)
    {
        if (i < 0 || j < 0 || i > size() || j > size())
        {
            throw out_of_range("顶点不存在");
        }
        return true;
    }
    void printVector(vector<int> v)
    {
        for (auto x : v)
        {
            cout << x << ' ';
        }
        cout << endl;
    }
    void printVectorMatrix(vector<vector<int>> mat)
    {
        for (vector<int> &row : mat)
        {
            for (auto x : row)
            {
                cout << x << ' ';
            }
            cout << endl;
        }
        cout << endl;
    }

public:
    /*构造方法*/
    GraphAdjMat(const vector<int> &vertices, const vector<vector<int>> &edges)
    {
        for (int val : vertices)
        {
            addVertex(val);
        }
        for (const vector<int> &edge : edges)
        {
            addEdge(edge[0], edge[1]);
        }
    }

    /*节点的数量*/
    int size()
    {
        return vertices.size();
    }

    /*添加顶点*/
    void addVertex(int val)
    {
        int n = size();
        vertices.push_back(val);                // 添加节点
        adjMat.emplace_back(vector<int>(n, 0)); // 插入一行
        // 为每一行最后插入一个0，相当于添加了一列
        for (vector<int> &row : adjMat)
        {
            row.push_back(0);
        }
    }

    /*删除顶点*/
    void deleteVertex(int index)
    {
        if (index > size())
        {
            throw out_of_range("顶点不存在");
        }
        vertices.erase(vertices.begin() + index); // 删除下标为index的顶点
        // 删除下标为index的行
        adjMat.erase(adjMat.begin() + index);
        // 删除对应下标的列
        for (vector<int> &row : adjMat)
        {
            row.erase(row.begin() + index);
        }
    }

    /*添加边*/
    void addEdge(int i, int j)
    {
        if (boundaryCheck(i, j))
        {
            adjMat[i][j] = 1;
            adjMat[j][i] = 1;
        }
    }

    /*删除边*/
    void deleteEdge(int i, int j)
    {
        if (boundaryCheck(i, j))
        {
            adjMat[i][j] = 0;
            adjMat[j][i] = 0;
        }
    }

    /*打印*/
    void Print()
    {
        cout << "顶点列表 = ";
        printVector(vertices);
        cout << "邻接矩阵 = " << endl;
        printVectorMatrix(adjMat);
    }
};

// driver code
int main()
{
    vector<int> ver = {1, 2, 3, 4, 5};
    vector<vector<int>> edges = {{0, 1}, {1, 2}, {2, 3}, {3, 4}};
    GraphAdjMat *G = new GraphAdjMat(ver, edges);
    G->Print();
}
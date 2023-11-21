/*�����ڽӾ����ʵ��*/

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
            throw out_of_range("���㲻����");
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
    /*���췽��*/
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

    /*�ڵ������*/
    int size()
    {
        return vertices.size();
    }

    /*��Ӷ���*/
    void addVertex(int val)
    {
        int n = size();
        vertices.push_back(val);                // ��ӽڵ�
        adjMat.emplace_back(vector<int>(n, 0)); // ����һ��
        // Ϊÿһ��������һ��0���൱�������һ��
        for (vector<int> &row : adjMat)
        {
            row.push_back(0);
        }
    }

    /*ɾ������*/
    void deleteVertex(int index)
    {
        if (index > size())
        {
            throw out_of_range("���㲻����");
        }
        vertices.erase(vertices.begin() + index); // ɾ���±�Ϊindex�Ķ���
        // ɾ���±�Ϊindex����
        adjMat.erase(adjMat.begin() + index);
        // ɾ����Ӧ�±����
        for (vector<int> &row : adjMat)
        {
            row.erase(row.begin() + index);
        }
    }

    /*��ӱ�*/
    void addEdge(int i, int j)
    {
        if (boundaryCheck(i, j))
        {
            adjMat[i][j] = 1;
            adjMat[j][i] = 1;
        }
    }

    /*ɾ����*/
    void deleteEdge(int i, int j)
    {
        if (boundaryCheck(i, j))
        {
            adjMat[i][j] = 0;
            adjMat[j][i] = 0;
        }
    }

    /*��ӡ*/
    void Print()
    {
        cout << "�����б� = ";
        printVector(vertices);
        cout << "�ڽӾ��� = " << endl;
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
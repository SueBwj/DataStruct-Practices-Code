#include < iostream>
using namespace std;
#define MAXSIZE 50

typedef struct GNode
{
    int Tag; // 0表示该节点是单元素，1表示该节点是广义表
    union
    {
        int data;
        struct GNode *Sublist;
    } URegion;
    struct GNode *Next;
} GList;

typedef enum
{
    Head,
    Term
} NodeTag;
typedef struct MatrixNode *PtrMatrix;
typedef struct TermNode
{
    int Row;
    int Col;
    int value;
};
typedef struct MatrixNode
{
    PtrMatrix Down;
    PtrMatrix Right;
    NodeTag Tag;
    union
    {
        PtrMatrix Next;
        TermNode Term;
    } URegion;
};
PtrMatrix HeadNode[MAXSIZE];
#include <iostream>
using namespace std;

struct PolyNode
{
    int coef;
    int expon;
    struct PolyNode *link;
    PolyNode() : link(nullptr) {}
    PolyNode(int c, int e) : coef(c), expon(e), link(nullptr) {}
};
typedef struct PolyNode *Polynomial;

// 多项式的加法运算
Polynomial PolyAdd(Polynomial P1, Polynomial P2)
{
    Polynomial front, rear;
    rear = new PolyNode();
    front = rear;
    rear->link = nullptr;
    while (P1 && P2)
    {
        rear->link = new PolyNode();
        rear = rear->link;
        if (P1->expon == P2->expon)
        {
            rear->expon = P1->expon;
            rear->coef = P1->coef + P2->coef;
            P1 = P1->link;
            P2 = P2->link;
        }
        else if (P1->expon < P2->expon)
        {
            rear->expon = P1->expon;
            rear->coef = P1->coef;

            P1 = P1->link;
        }
        else
        {
            rear->expon = P2->expon;
            rear->coef = P2->coef;

            P2 = P2->link;
        }
    }
    while (P1)
    {
        rear->link = new PolyNode();
        rear = rear->link;
        rear->expon = P1->expon;
        rear->coef = P1->coef;

        P1 = P1->link;
    }
    while (P2)
    {
        rear->link = new PolyNode();
        rear = rear->link;
        rear->expon = P2->expon;
        rear->coef = P2->coef;

        P2 = P2->link;
    }
    return front->link;
}

int PolyLength(Polynomial P)
{
    if (P == nullptr)
    {
        return 0;
    }
    else
    {
        return 1 + PolyLength(P->link);
    }
}

void destroyPolynomial(Polynomial P)
{
    if (P == nullptr)
    {
        return;
    }
    else
    {
        destroyPolynomial(P->link);
        delete (P);
    }
}

Polynomial PolyMultiple(Polynomial P1, Polynomial P2)
{
    int len1 = PolyLength(P1);
    int len2 = PolyLength(P2);
    Polynomial front, rear;
    rear = new PolyNode(0, 0);
    front = rear;
    rear->link = nullptr;
    Polynomial P1tmp = P1;
    for (int i = 0; i < len1; i++)
    {
        Polynomial frontTmp, rearTmp;
        rearTmp = new PolyNode(0, 0);
        frontTmp = rearTmp;
        Polynomial tmp = P2;
        for (int j = 0; j < len2; j++)
        {
            rearTmp->link = new PolyNode();
            rearTmp = rearTmp->link;
            rearTmp->coef = P1tmp->coef * tmp->coef;
            rearTmp->expon = P1tmp->expon + tmp->expon;
            tmp = tmp->link;
        }
        P1tmp = P1tmp->link;
        rearTmp->link = nullptr;
        Polynomial ansTmp = PolyAdd(frontTmp, front);
        destroyPolynomial(front);
        destroyPolynomial(frontTmp);
        front = ansTmp;
    }
    return front->link;
}

void PrintPolynomial(Polynomial P)
{
    while (P)
    {
        cout << P->coef << "x^" << P->expon << " ";
        P = P->link;
    }
    cout << endl;
}

// driver code
int main()
{
    // 3x^2 + 3x^3 + 4x^5 + 7x^6 -3x^9
    Polynomial P1 = new PolyNode(3, 4);
    P1->link = new PolyNode(-5, 2);
    P1->link->link = new PolyNode(6, 1);
    P1->link->link->link = new PolyNode(-2, 0);
    Polynomial P2 = new PolyNode(5, 20);
    P2->link = new PolyNode(-7, 4);
    P2->link->link = new PolyNode(3, 1);

    // ans = 6x^2 + 6x^3 + 8x^5 + 14x^6 -6x^9
    Polynomial ans = PolyMultiple(P1, P2);
    PrintPolynomial(ans);
}
// ���� 1���� �� �������� �Ҵ��ص���(�Է¹޴� �Լ� �ʿ� ����)
// �׳� ����, ������ �����ϸ��

// ���� 2��. MAX_NUMBER �� �����ؼ� ũ�� ����
// fread, fwrite

#include <stdio.h>
#include <stdlib.h>

#define PROB 1

#if PROB == 1

typedef struct PolyNode
{
    int coef;
    int exp;
    struct PolyNode *link;
} node;

void addNode(node **, int, int);
void printList(node *);
void freeAllNode(node *);

node *addPoly(node *, node *);
node *mulPoly(node *, node *);

int main(void)
{
    node *a = NULL;
    addNode(&a, 3, 5);
    addNode(&a, 4, 3);
    addNode(&a, -2, 2);
    addNode(&a, 1, 1);
    addNode(&a, 7, 0);
    node *b = NULL;
    addNode(&b, 4, 3);
    addNode(&b, 2, 2);
    addNode(&b, -6, 1);
    addNode(&b, -3, 0);

    printf("a(x) = ");
    printList(a);
    printf("b(x) = ");
    printList(b);

    node *c = addPoly(a, b);
    printf("c(x) = ");
    printList(c);

    node *d = mulPoly(a, b);
    printf("d(x) = ");
    printList(d);
}

void addNode(node **head, int coef, int exp)
{
    node *lastNode = *head;

    node *newNode = (node *)malloc(sizeof(node));
    newNode->coef = coef;
    newNode->exp = exp;
    newNode->link = NULL;

    if (*head == NULL)
        *head = newNode;
    else
    {
        while (lastNode->link != NULL)
            lastNode = lastNode->link;
        lastNode->link = newNode;
    }
}

void printList(node *p)
{
    while (1)
    {
        printf("%dx^%d\t", p->coef, p->exp);
        if (p->link == NULL)
            break;
        p = p->link;
    }
    printf("\n");
}

void freeAllNode(node *p)
{
    while (p->link != NULL)
    {
        node *delNode = p;
        p = p->link;
        free(delNode);
    }
    free(p);
}

node *addPoly(node *a, node *b)
{
    node *addhead = NULL;
    // �� ����Ʈ�� ���� ��ġ�� ������ ��
    // if a == b �׳� ���� �� c�� ���� �� a, b �� �� ���� ��ҷ� �̵�
    // if a > b a�� ���� c�� ���� �� a�� ���� ��ҷ� �̵�, b�� �״��
    // if a < b b�� ���� c�� ���� �� b�� ���� ��ҷ� �̵�, a�� �״��
    while (a != NULL && b != NULL)
    {
        if (a->exp == b->exp)
        {
            if ((a->coef + b->coef) != 0)
                addNode(&addhead, (a->coef + b->coef), a->exp);
            a = a->link;
            b = b->link;
        }
        else if (a->exp > b->exp)
        {
            addNode(&addhead, a->coef, a->exp);
            a = a->link;
        }
        else if (a->exp < b->exp)
        {
            addNode(&addhead, b->coef, b->exp);
            b = b->link;
        }
    }
    while (a != NULL)
    {
        if (a->coef != 0)
            addNode(&addhead, a->coef, a->exp);
        a = a->link;
    }
    while (b != NULL)
    {
        if (b->coef != 0)
            addNode(&addhead, b->coef, b->exp);
        b = b->link;
    }

    return addhead;
}

node *mulPoly(node *a, node *b)
{
    // a�� ���Ḯ��Ʈ���� b�� �� �������� ���ؼ� �� a�� ��Ҹ�ŭ�� ���׽� ���Ḯ��Ʈ�� �����
    // �� ���Ḯ��Ʈ���� ���� ���ؼ� ������ ����?
    // �ٵ� �̷��� �Ǹ� ���׽��� �ʹ� ũ�� �ʹ� ���� ���Ḯ��Ʈ�� �����ϰԵ�
    node *mulhead = NULL;
    addNode(&mulhead, 0, 0);

    while (a != NULL)
    {
        node *templist = NULL;
        node *cur = b;
        while (1)
        {
            addNode(&templist, (a->coef * cur->coef), (a->exp + cur->exp));
            cur = cur->link;
            if (cur == NULL)
                break;
        }
        mulhead = addPoly(mulhead, templist);
        a = a->link;
    }
    return mulhead;
}

#elif PROB == 2

#endif
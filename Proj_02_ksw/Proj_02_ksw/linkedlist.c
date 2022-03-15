#include "linkedlist.h"

void addNode(node** head, int num)
{
    node* lastNode = *head;

    node* newNode = (node*)malloc(sizeof(node));
    newNode->num = num;
    newNode->link = NULL;

    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        while (lastNode->link != NULL)  // lastNode->link �̷��Ը� �ᵵ NULL�� ������ while�� Ż��
        {
            lastNode = lastNode->link;
        }

        lastNode->link = newNode;
    }
    return; // void �Լ� ������ �׻� return; ���ֱ�
}

void printNode(node* p)
{
    while (1)
    {
        printf("%d\t", p->num);
        if (p->link == NULL)
            break;
        p = p->link;
    }
}

void freeAllNode(node* p)
{
    while (p->link != NULL)
    {
        node* delNode = p;
        p = p->link;
        free(delNode);
    }
    free(p);
}
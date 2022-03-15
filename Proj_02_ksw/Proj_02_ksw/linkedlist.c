#include "linkedlist.h"

void addNode(node **head, int num)
{
    static int k;

    node *current = *head;
    node *prev = *head;

    node *newNode = (node *)malloc(sizeof(node));
    newNode->num = num;
    newNode->link = NULL;

    if (*head == NULL)
    {
        *head = newNode;
        return;
    }
    else if (current->num > num)
    {
        printf("ù if�� ����\n");
        *head = newNode;
        newNode->link = current;
        return;
        printf("ù if�� ��\n");
    }
    else
    {
        while (current->num < num) // 2���� �߰��� ��Ȳ���� ����
        {
            printf("%d��° while�� ����\n", k);
            if (current->link == NULL)
            {
                current->link = newNode;
                return;
            }
            prev = current;
            current = current->link;
            printf("while�� �� : %d, %d\n", current->num, num);
        }
        printf("while�� Ż��\n");
        newNode->link = current;
        prev->link = newNode;
    }
    ++k;
    return;
}

void printNode(node *p)
{
    while (1)
    {
        printf("%d\t", p->num);
        if (p->link == NULL)
            break;
        p = p->link;
    }
    return;
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
    return;
}
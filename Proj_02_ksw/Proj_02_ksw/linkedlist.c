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
        printf("첫 if문 시작\n");
        *head = newNode;
        newNode->link = current;
        return;
        printf("첫 if문 끝\n");
    }
    else
    {
        while (current->num < num) // 2개가 추가된 상황에서 에러
        {
            printf("%d번째 while문 시작\n", k);
            if (current->link == NULL)
            {
                current->link = newNode;
                return;
            }
            prev = current;
            current = current->link;
            printf("while문 끝 : %d, %d\n", current->num, num);
        }
        printf("while문 탈출\n");
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
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
        while (lastNode->link != NULL)  // lastNode->link 이렇게만 써도 NULL을 만나면 while문 탈출
        {
            lastNode = lastNode->link;
        }

        lastNode->link = newNode;
    }
    return; // void 함수 끝에도 항상 return; 해주기
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
#include "linkedlist.h"

// void addNode(node **head, int num)
// {
//     static int k;

//     node *current = *head;
//     node *prev = *head;

//     node *newNode = (node *)malloc(sizeof(node));
//     newNode->num = num;
//     newNode->link = NULL;

//     if (*head == NULL)
//     {
//         *head = newNode;
//         return;
//     }
//     else if (current->num > num)
//     {
//         *head = newNode;
//         newNode->link = current;
//         return;
//     }
//     else
//     {
//         while (current->num < num) // 2개가 추가된 상황에서 에러
//         {
//             if (current->link == NULL)
//             {
//                 current->link = newNode;
//                 return;
//             }
//             prev = current;
//             current = current->link;
//         }
//         newNode->link = current;
//         prev->link = newNode;
//     }
//     ++k;
//     return;
// }

void addNode(node **head, int num)
{
    node *newNode = (node *)malloc(sizeof(node));
    newNode->num = num;
    newNode->link = NULL;

    node *pos = *head;

    if (*head == NULL)
    {
        *head = newNode;
    }
    else if (num >= (*head)->num)
    {
        newNode->link = *head;
        *head = newNode;
    }
    else
    {
        while (1)
        {
            if (pos->link == NULL)
            {
                pos->link = newNode;
                break;
            }
            else if (pos->link->num > num)
            {
                newNode->link = pos->link;
                pos->link = newNode;
                break;
            }
            pos = pos->link;
        }
    }
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
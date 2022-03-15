#pragma once    // ��� ���� �����̾���?
#define _CRT_SECURE_NO_WARNINGS // �ٸ� ��� ���Ϻ��� ���� ���;���

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

void addNode(node** head, int id, char name[])
{
    node* lastNode = *head;

    node* newNode = (node*)malloc(sizeof(node));
    newNode->id = id;
    strcpy(newNode->name, name);
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
node* searchNode(node* p, int id)
{
    while (p->id != id)
    {
        p = p->link;
    }
    return p;
}
node* deleteNode(node** p, int id)
{
    node* cur = *p;
    node* prev = NULL;

    if (cur->id == id)
    {
        *p = cur->link;
    }
    else
    {
        do
        {
            prev = cur;
            cur = cur->link;
        } while (cur->id != id);

        prev->link = cur->link;
    }
    return cur;
}
void printNode(node* p)
{
    while (1)
    {
        printf("id : %d, name %s\n", p->id, p->name);
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
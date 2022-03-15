#pragma once    // 얘는 무슨 역할이었지?
#define _CRT_SECURE_NO_WARNINGS // 다른 헤더 파일보다 위에 나와야함

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
        while (lastNode->link != NULL)  // lastNode->link 이렇게만 써도 NULL을 만나면 while문 탈출
        {
            lastNode = lastNode->link;
        }

        lastNode->link = newNode;
    }
    return; // void 함수 끝에도 항상 return; 해주기
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
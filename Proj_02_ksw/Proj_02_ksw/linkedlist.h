#ifndef __LINKEDLIST_H__    //�ߺ� ���� ��԰� �־���...
#define __LINKEDLIST_H__
#pragma warning(diable:4996)

#define _CRT_SECURE_NO_WARNINGS // �ٸ� ��� ���Ϻ��� ���� ���;���

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//���⿡ �ٸ� ��� ���� �����ϸ��

typedef struct NODE
{
    int num;
    struct NODE* link;
} node;

void addNode(node** head, int num);
void printNode(node* p);
void freeAllNode(node* p);

#endif
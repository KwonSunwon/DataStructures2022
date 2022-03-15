#ifndef __LINKEDLIST_H__    //중복 방지 까먹고 있었다...
#define __LINKEDLIST_H__
#pragma warning(diable:4996)

#define _CRT_SECURE_NO_WARNINGS // 다른 헤더 파일보다 위에 나와야함

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//여기에 다른 헤더 전부 정의하면됨

typedef struct NODE
{
    int num;
    struct NODE* link;
} node;

void addNode(node** head, int num);
void printNode(node* p);
void freeAllNode(node* p);

#endif
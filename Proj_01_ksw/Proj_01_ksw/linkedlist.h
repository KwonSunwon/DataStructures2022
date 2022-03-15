#ifndef __LINKEDLIST_H__    //중복 방지 까먹고 있었다...
#define __LINKEDLIST_H__

//여기에 다른 헤더 전부 정의하면됨

typedef struct NODE
{
    int id;
    char name[10];
    struct NODE* link;
} node;

void addNode(node** head, int id, char name[]);
node* searchNode(node* p, int id);
node* deleteNode(node** p, int id);
void printNode(node* p);
void freeAllNode(node* p);

#endif
#ifndef __LINKEDLIST_H__    //�ߺ� ���� ��԰� �־���...
#define __LINKEDLIST_H__

//���⿡ �ٸ� ��� ���� �����ϸ��

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
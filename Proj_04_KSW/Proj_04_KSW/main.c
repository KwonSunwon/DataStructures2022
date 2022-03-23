// ���� 1���� �� �������� �Ҵ��ص���(�Է¹޴� �Լ� �ʿ� ����)
// �׳� ����, ������ �����ϸ��

// ���� 2��. MAX_NUMBER �� �����ؼ� ũ�� ����
// fread, fwrite

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROB 2

#if PROB == 1

typedef struct PolyNode
{
    int coef;
    int exp;
    struct PolyNode *link;
} node;

void addNode(node **, int, int);
void printList(node *);
void freeAllNode(node *);

node *addPoly(node *, node *);
node *mulPoly(node *, node *);

int main(void)
{
    node *a = NULL;
    addNode(&a, 3, 5);
    addNode(&a, 4, 3);
    addNode(&a, -2, 2);
    addNode(&a, 1, 1);
    addNode(&a, 7, 0);
    node *b = NULL;
    addNode(&b, 4, 3);
    addNode(&b, 2, 2);
    addNode(&b, -6, 1);
    addNode(&b, -3, 0);

    printf("a(x) = ");
    printList(a);
    printf("b(x) = ");
    printList(b);

    node *c = addPoly(a, b);
    printf("c(x) = ");
    printList(c);

    node *d = mulPoly(a, b);
    printf("d(x) = ");
    printList(d);
}

void addNode(node **head, int coef, int exp)
{
    node *lastNode = *head;

    node *newNode = (node *)malloc(sizeof(node));
    newNode->coef = coef;
    newNode->exp = exp;
    newNode->link = NULL;

    if (*head == NULL)
        *head = newNode;
    else
    {
        while (lastNode->link != NULL)
            lastNode = lastNode->link;
        lastNode->link = newNode;
    }
}

void printList(node *p)
{
    while (1)
    {
        printf("%dx^%d\t", p->coef, p->exp);
        if (p->link == NULL)
            break;
        p = p->link;
    }
    printf("\n");
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
}

node *addPoly(node *a, node *b)
{
    node *addhead = NULL;
    // �� ����Ʈ�� ���� ��ġ�� ������ ��
    // if a == b �׳� ���� �� c�� ���� �� a, b �� �� ���� ��ҷ� �̵�
    // if a > b a�� ���� c�� ���� �� a�� ���� ��ҷ� �̵�, b�� �״��
    // if a < b b�� ���� c�� ���� �� b�� ���� ��ҷ� �̵�, a�� �״��
    while (a != NULL && b != NULL)
    {
        if (a->exp == b->exp)
        {
            if ((a->coef + b->coef) != 0)
                addNode(&addhead, (a->coef + b->coef), a->exp);
            a = a->link;
            b = b->link;
        }
        else if (a->exp > b->exp)
        {
            addNode(&addhead, a->coef, a->exp);
            a = a->link;
        }
        else if (a->exp < b->exp)
        {
            addNode(&addhead, b->coef, b->exp);
            b = b->link;
        }
    }
    while (a != NULL)
    {
        if (a->coef != 0)
            addNode(&addhead, a->coef, a->exp);
        a = a->link;
    }
    while (b != NULL)
    {
        if (b->coef != 0)
            addNode(&addhead, b->coef, b->exp);
        b = b->link;
    }

    return addhead;
}

node *mulPoly(node *a, node *b)
{
    // a�� ���Ḯ��Ʈ���� b�� �� �������� ���ؼ� �� a�� ��Ҹ�ŭ�� ���׽� ���Ḯ��Ʈ�� �����
    // �� ���Ḯ��Ʈ���� ���� ���ؼ� ������ ����?
    // �ٵ� �̷��� �Ǹ� ���׽��� �ʹ� ũ�� �ʹ� ���� ���Ḯ��Ʈ�� �����ϰԵ�
    node *mulhead = NULL;
    addNode(&mulhead, 0, 0);

    while (a != NULL)
    {
        node *templist = NULL;
        node *cur = b;
        while (1)
        {
            addNode(&templist, (a->coef * cur->coef), (a->exp + cur->exp));
            cur = cur->link;
            if (cur == NULL)
                break;
        }
        mulhead = addPoly(mulhead, templist);
        a = a->link;
    }
    return mulhead;
}

#elif PROB == 2

#define FNAME "namecard.bin"
#define MAX_NUMBER 10

typedef struct nameCard
{
    char name[5];
    int company;
    int phone;
} card;

void printf_menu();

int init(card *);
void finalize(card *, int);

void addCard(card *, int);
void printCard(card *, int);
void searchCard(card *, int);
void delCard(card *, int *);

int main(void)
{
    card NC[MAX_NUMBER] = {'\0', 0, 0};

    // char answer;
    int menuItem;
    int count = 0;
    count = init(NC);

    while (1)
    {
        printf_menu();
        scanf("%d", &menuItem);
        printf("\n");
        switch (menuItem)
        {
        case 1:
            printf("���� �Է�\n");
            printf("---------------------\n");
            addCard(NC, count++);
            break;
        case 2:
            printf("���� ���\n");
            printf("---------------------\n");
            printCard(NC, count);
            break;
        case 3:
            printf("���� �˻�\n");
            printf("---------------------\n");
            searchCard(NC, count);
            break;
        case 4:
            printf("���� ����\n");
            printf("---------------------\n");
            delCard(NC, &count);
            break;
        case 5:
            printf("���α׷� ����\n");
            finalize(NC, count);
            return;
        }
    }
}

void printf_menu()
{
    printf("\n=============Name Card DBMS=============\n");
    printf("��ɾ �����ϼ���.\n");
    printf("1. ���� �Է�\n");
    printf("2. ��� ���� ���\n");
    printf("3. ���� �˻�\n");
    printf("4. ���� ����\n");
    printf("5. ����\n");
    printf(" ��� �Է� ---> ");
}

int init(card *NC)
{
    FILE *fp = fopen(FNAME, "rb");
    if (fp == NULL)
    {
        printf("���ο� ���� ����\n");
        fp = fopen(FNAME, "w+");
        fclose(fp);
        return 0;
    }
    int count = 0;
    fseek(fp, 0, SEEK_END);
    count = ftell(fp) / sizeof(card);
    fread(NC, sizeof(card), count, fp);
    fclose(fp);
    return count;
}

void finalize(card *NC, int count)
{
    if (count == 0)
        return;

    FILE *fp = fopen(FNAME, "wb");
    if (fp == NULL)
    {
        printf("���� ���� ����\n");
        exit(-1);
    }
    fwrite(NC, sizeof(card), count, fp);
    fclose(fp);
}

void addCard(card *NC, int count)
{
    char name[4] = {'\0'};
    int company, phone;
    printf("�̸� : ");
    scanf("%s", &name);
    printf("ȸ�� : ");
    scanf("%d", &company);
    printf("��ȭ : ");
    scanf("%d", &phone);

    strcpy(NC[count].name, name);
    NC[count].company = company;
    NC[count].phone = phone;
}

void printCard(card *NC, int count)
{
    printf("��� ���� ���\n");
    for (int i = 0; i < count; ++i)
        printf("%d. �̸�:%s, ȸ��:%d, ��ȭ:%d\n", i, NC[i].name, NC[i].company, NC[i].phone);
    printf("%d���� ������ ������\n", count);
}

void searchCard(card *NC, int count)
{
    char key[4];
    printf("�˻��� �̸��� �Է��ϼ���. : ");
    scanf("%s", key);

    int searchCount = 0;

    for (int i = 0; i < count; ++i)
    {
        if (strstr(NC[i].name, key) != NULL)
        {
            printf("�˻��� ���� �̸� : ");
            printf("�̸�:%s, ȸ��:%d, ��ȭ:%d\n", NC[i].name, NC[i].company, NC[i].phone);
            ++searchCount;
        }
    }
    printf("%d���� ���� �˻���\n", searchCount);
}

void delCard(card *NC, int *count)
{
    char key[4];
    printf("������ �̸��� �Է��ϼ���. : ");
    scanf("%s", key);

    int delCount = 0;

    for (int i = 0; i < *count; ++i)
    {
        if (strcmp(NC[i].name, key) == 0)
        {
            printf("���� ���� �̸� : ");
            printf("�̸�:%s, ȸ��:%d, ��ȭ:%d\n", NC[i].name, NC[i].company, NC[i].phone);
            for (int j = i; j < *count - 1; ++j)
            {
                NC[j] = NC[j + 1];
            }
            --*count;
            ++delCount;
        }
    }
    printf("%d���� ���� ������", delCount);
}

#endif
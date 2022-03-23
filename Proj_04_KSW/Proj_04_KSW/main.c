// 문제 1번에 값 정적으로 할당해도됨(입력받는 함수 필요 없음)
// 그냥 덧셈, 곱셈만 구현하면됨

// 문제 2번. MAX_NUMBER 로 정의해서 크기 결정
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
    // 두 리스트의 현재 위치의 차수를 비교
    // if a == b 그냥 더한 후 c에 저장 후 a, b 둘 다 다음 요소로 이동
    // if a > b a의 값을 c에 저장 후 a는 다음 요소로 이동, b는 그대로
    // if a < b b의 값을 c에 저장 후 b는 다음 요소로 이동, a는 그대로
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
    // a의 연결리스트마다 b의 각 차수들을 곱해서 총 a의 요소만큼의 다항식 연결리스트를 만들고
    // 그 연결리스트들을 전부 더해서 최종값 구함?
    // 근데 이렇게 되면 다항식이 너무 크면 너무 많은 연결리스트를 생성하게됨
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
            printf("명함 입력\n");
            printf("---------------------\n");
            addCard(NC, count++);
            break;
        case 2:
            printf("명함 출력\n");
            printf("---------------------\n");
            printCard(NC, count);
            break;
        case 3:
            printf("명함 검색\n");
            printf("---------------------\n");
            searchCard(NC, count);
            break;
        case 4:
            printf("명함 삭제\n");
            printf("---------------------\n");
            delCard(NC, &count);
            break;
        case 5:
            printf("프로그램 종료\n");
            finalize(NC, count);
            return;
        }
    }
}

void printf_menu()
{
    printf("\n=============Name Card DBMS=============\n");
    printf("명령어를 선택하세요.\n");
    printf("1. 명함 입력\n");
    printf("2. 모든 명함 출력\n");
    printf("3. 명함 검색\n");
    printf("4. 명함 삭제\n");
    printf("5. 종료\n");
    printf(" 명령 입력 ---> ");
}

int init(card *NC)
{
    FILE *fp = fopen(FNAME, "rb");
    if (fp == NULL)
    {
        printf("새로운 파일 생성\n");
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
        printf("파일 오픈 실패\n");
        exit(-1);
    }
    fwrite(NC, sizeof(card), count, fp);
    fclose(fp);
}

void addCard(card *NC, int count)
{
    char name[4] = {'\0'};
    int company, phone;
    printf("이름 : ");
    scanf("%s", &name);
    printf("회사 : ");
    scanf("%d", &company);
    printf("전화 : ");
    scanf("%d", &phone);

    strcpy(NC[count].name, name);
    NC[count].company = company;
    NC[count].phone = phone;
}

void printCard(card *NC, int count)
{
    printf("모든 명함 출력\n");
    for (int i = 0; i < count; ++i)
        printf("%d. 이름:%s, 회사:%d, 전화:%d\n", i, NC[i].name, NC[i].company, NC[i].phone);
    printf("%d개의 명함이 존재함\n", count);
}

void searchCard(card *NC, int count)
{
    char key[4];
    printf("검색할 이름을 입력하세요. : ");
    scanf("%s", key);

    int searchCount = 0;

    for (int i = 0; i < count; ++i)
    {
        if (strstr(NC[i].name, key) != NULL)
        {
            printf("검색한 명함 이름 : ");
            printf("이름:%s, 회사:%d, 전화:%d\n", NC[i].name, NC[i].company, NC[i].phone);
            ++searchCount;
        }
    }
    printf("%d개의 명함 검색함\n", searchCount);
}

void delCard(card *NC, int *count)
{
    char key[4];
    printf("삭제할 이름을 입력하세요. : ");
    scanf("%s", key);

    int delCount = 0;

    for (int i = 0; i < *count; ++i)
    {
        if (strcmp(NC[i].name, key) == 0)
        {
            printf("삭제 명함 이름 : ");
            printf("이름:%s, 회사:%d, 전화:%d\n", NC[i].name, NC[i].company, NC[i].phone);
            for (int j = i; j < *count - 1; ++j)
            {
                NC[j] = NC[j + 1];
            }
            --*count;
            ++delCount;
        }
    }
    printf("%d개의 명함 삭제함", delCount);
}

#endif
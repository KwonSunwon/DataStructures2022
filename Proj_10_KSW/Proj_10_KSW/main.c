#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct _Element
{
    int row;
    int col;
    int value;
} Element;

typedef struct _Node
{
    Element data;
    struct _Node *link;
} Node;

typedef struct _Head
{
    int m_row, m_col;
    Node *link;
} Head;

void init(Head *);
void add(Head *, Element);

Head *add_matrix(Head mat_a, Head mat_b); // 두 행렬 더하는 함수
Head *sub_matrix(Head mat_a, Head mat_b); // 두 행렬의 뺄셈을 수행하는 함수
Head *matrix_transpose(Head h);           // 전치 행렬을 구하는 함수
void display_matrix(Head *h);             // 행렬 형태로 출력
void display_list(Head *h);               // 리스트 형식으로 출력

void free_matrix(Head *);

// < test.txt -> scanf()로 입력 받기 가능
// > result.txt -> printf()로 출력 가능

int main()
{
    Head mat_a, mat_b;
    Head *mat_c, *mat_d, *mat_e;

    // 문제 내용을 해결하기 위한 코드 추가
    int row, col;
    scanf("%d %d", &row, &col);

    init(&mat_a);
    init(&mat_b);

    mat_c = NULL;
    mat_d = NULL;
    mat_e = NULL;

    mat_a.m_row = row;
    mat_a.m_col = col;

    mat_b.m_row = row;
    mat_b.m_col = col;

    for (int i = 0; i < row; ++i)
        for (int j = 0; j < col; ++j)
        {
            int data;
            scanf("%d", &data);
            Element element = {i, j, data};
            add(&mat_a, element);
        }

    for (int i = 0; i < row; ++i)
        for (int j = 0; j < col; ++j)
        {
            int data;
            scanf("%d", &data);
            Element element = {i, j, data};
            add(&mat_b, element);
        }

    printf("행렬 A\n");
    display_matrix(&mat_a);
    printf("\n");

    printf("행렬 A 리스트\n");
    display_list(&mat_a);
    printf("\n");

    printf("행렬 B\n");
    display_matrix(&mat_b);
    printf("\n");

    printf("행렬 B 리스트\n");
    display_list(&mat_b);
    printf("\n");

    mat_c = add_matrix(mat_a, mat_b);

    printf("행렬 C = A + B\n");
    display_matrix(mat_c);
    printf("\n");

    printf("행렬 C 리스트\n");
    display_list(mat_c);
    printf("\n");

    mat_d = sub_matrix(mat_a, mat_b);

    printf("행렬 D = A - B\n");
    display_matrix(mat_d);
    printf("\n");

    printf("행렬 D 리스트\n");
    display_list(mat_d);
    printf("\n");

    mat_e = matrix_transpose(mat_a);

    printf("행렬 E = TRANSPOSE(A)\n");
    display_matrix(mat_e);
    printf("\n");

    printf("행렬 E 리스트\n");
    display_list(mat_e);
    printf("\n");

    // 동적 할당된 메모리 모두 해제
    free_matrix(&mat_a);
    free_matrix(&mat_b);
    free_matrix(mat_c);
    free_matrix(mat_d);
    free_matrix(mat_e);
    if (mat_c->link != NULL)
        free(mat_c);
    mat_c = NULL;
    if (mat_d->link != NULL)
        free(mat_d);
    mat_d = NULL;
    if (mat_e->link != NULL)
        free(mat_e);
    mat_e = NULL;
}

void init(Head *h)
{
    h->link = NULL;
}

void add(Head *h, Element e)
{
    if (e.value == 0)
        return;

    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = e;
    newNode->link = NULL;

    Node *pos = h->link;

    if (h->link == NULL)
    {
        h->link = newNode;
        return;
    }
    else if (pos->data.row >= e.row)
    {
        if (pos->data.row == e.row)
            if (pos->data.col > e.col)
            {
                newNode->link = h->link;
                h->link = newNode;
                return;
            }
        if (pos->data.row > e.row)
        {
            newNode->link = h->link;
            h->link = newNode;
            return;
        }
    }

    while (pos->link != NULL)
    {
        if (pos->link->data.row >= e.row)
        {
            if (pos->link->data.row > e.row)
            {
                newNode->link = pos->link;
                pos->link = newNode;
                return;
            }
            else if (pos->link->data.row == e.row)
            {
                while (pos->link != NULL)
                {
                    if (pos->link->data.col > e.col)
                    {
                        newNode->link = pos->link;
                        pos->link = newNode;
                        return;
                    }
                    if (pos->link->data.row > e.row)
                    {
                        newNode->link = pos->link;
                        pos->link = newNode;
                        return;
                    }
                    pos = pos->link;
                }
                pos->link = newNode;
            }
            return;
        }
        pos = pos->link;
    }
    pos->link = newNode;
}

Head *add_matrix(Head mat_a, Head mat_b)
{
    Head *mat_result = (Head *)malloc(sizeof(Head));

    init(mat_result);
    mat_result->m_row = mat_a.m_row;
    mat_result->m_col = mat_b.m_col;

    if (mat_a.m_row == 1 && mat_a.m_col == 1)
    {
        int a = 1;
        int b = 1;
        Element element;
        element.row = 1;
        element.col = 1;
        if (mat_a.link == NULL)
            a = 0;
        if (mat_b.link == NULL)
            b = 0;
        element.value = a + b;

        add(mat_result, element);
        return;
    }

    Node *aCur = mat_a.link;
    Node *bCur = mat_b.link;

    int aEndFlag = 0;
    int bEndFlag = 0;
    int addFlag = 0;

    if (aCur == NULL)
        aEndFlag = 1;

    if (bCur == NULL)
        bEndFlag = 1;

    for (int i = 0; i < mat_result->m_row; ++i)
    {
        for (int j = 0; j < mat_result->m_col; ++j)
        {
            if (aEndFlag == 0 && bEndFlag == 0)
            {
                if (aCur->data.row == i && aCur->data.col == j && bCur->data.row == i && bCur->data.col == j)
                {
                    Element element;
                    element.row = i;
                    element.col = j;
                    element.value = aCur->data.value + bCur->data.value;

                    add(mat_result, element);

                    aCur = aCur->link;
                    bCur = bCur->link;

                    addFlag = 1;
                }
            }
            if (aEndFlag == 0 && addFlag == 0)
            {
                if (aCur->data.row == i && aCur->data.col == j)
                {
                    Element element;
                    element.row = i;
                    element.col = j;
                    element.value = aCur->data.value;

                    add(mat_result, element);

                    aCur = aCur->link;
                }
            }
            if (bEndFlag == 0 && addFlag == 0)
            {
                if (bCur->data.row == i && bCur->data.col == j)
                {
                    Element element;
                    element.row = i;
                    element.col = j;
                    element.value = bCur->data.value;

                    add(mat_result, element);

                    bCur = bCur->link;
                }
            }

            if (aCur == NULL)
                aEndFlag = 1;
            if (bCur == NULL)
                bEndFlag = 1;
            addFlag = 0;
        }
    }

    return mat_result;
}

Head *sub_matrix(Head mat_a, Head mat_b)
{
    Head *mat_result = (Head *)malloc(sizeof(Head));

    init(mat_result);
    mat_result->m_row = mat_a.m_row;
    mat_result->m_col = mat_b.m_col;

    if (mat_a.m_row == 1 && mat_a.m_col == 1)
    {
        int a = 1;
        int b = 1;
        Element element;
        element.row = 1;
        element.col = 1;
        if (mat_a.link == NULL)
            a = 0;
        if (mat_b.link == NULL)
            b = 0;
        element.value = a - b;

        add(mat_result, element);
        return;
    }

    Node *aCur = mat_a.link;
    Node *bCur = mat_b.link;

    int aEndFlag = 0;
    int bEndFlag = 0;
    int subFlag = 0;

    if (aCur == NULL)
        aEndFlag = 1;

    if (bCur == NULL)
        bEndFlag = 1;

    for (int i = 0; i < mat_result->m_row; ++i)
    {
        for (int j = 0; j < mat_result->m_col; ++j)
        {
            if (aEndFlag == 0 && bEndFlag == 0)
            {
                if (aCur->data.row == i && aCur->data.col == j && bCur->data.row == i && bCur->data.col == j)
                {
                    Element element;
                    element.row = i;
                    element.col = j;
                    element.value = aCur->data.value - bCur->data.value;

                    add(mat_result, element);

                    aCur = aCur->link;
                    bCur = bCur->link;

                    subFlag = 1;
                }
            }
            if (aEndFlag == 0 && subFlag == 0)
            {
                if (aCur->data.row == i && aCur->data.col == j)
                {
                    Element element;
                    element.row = i;
                    element.col = j;
                    element.value = aCur->data.value;

                    add(mat_result, element);

                    aCur = aCur->link;
                }
            }
            if (bEndFlag == 0 && subFlag == 0)
            {
                if (bCur->data.row == i && bCur->data.col == j)
                {
                    Element element;
                    element.row = i;
                    element.col = j;
                    element.value = -bCur->data.value;

                    add(mat_result, element);

                    bCur = bCur->link;
                }
            }

            if (aCur == NULL)
                aEndFlag = 1;
            if (bCur == NULL)
                bEndFlag = 1;
            subFlag = 0;
        }
    }

    return mat_result;
}

Head *matrix_transpose(Head h)
{
    Head *mat_result = (Head *)malloc(sizeof(Head));

    init(mat_result);
    mat_result->m_row = h.m_col;
    mat_result->m_col = h.m_row;

    Node *cur = h.link;
    while (cur != NULL)
    {
        Element element;
        element.col = cur->data.row;
        element.row = cur->data.col;
        element.value = cur->data.value;

        add(mat_result, element);

        cur = cur->link;
    }

    return mat_result;
}

void display_matrix(Head *h)
{
    if (h->m_row == 1 && h->m_col == 1)
    {
        if (h->link == NULL)
            printf("0\n");
        else
            printf("%d\n", h->link->data.value);
        return;
    }

    Node *cur = h->link;
    int endFlag = 0;

    if (h->link == NULL)
        endFlag = 1;

    for (int i = 0; i < h->m_row; ++i)
    {
        for (int j = 0; j < h->m_col; ++j)
        {
            if (endFlag == 1)
            {
                printf("0 ");
            }
            else if (cur->data.row == i && cur->data.col == j)
            {
                printf("%d ", cur->data.value);
                cur = cur->link;
                if (cur == NULL)
                    endFlag = 1;
            }
            else
                printf("0 ");
        }
        printf("\n");
    }
}
void display_list(Head *h)
{
    Node *cur = h->link;
    while (cur != NULL)
    {
        printf("(%d, %d) %d\n", cur->data.row, cur->data.col, cur->data.value);
        cur = cur->link;
    }
}

void free_matrix(Head *h)
{
    while (h->link != NULL)
    {
        Node *delNode = h->link;
        h->link = delNode->link;
        free(delNode);
    }
}

// 이거 학기초에 다항식의 계산기 만들었던 부분에서 따와서 수정하면
// 더하고, 뻬는 연산 금방 가능할듯?
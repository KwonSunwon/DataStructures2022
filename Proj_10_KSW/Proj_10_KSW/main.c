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
    struct Node *link;
} Node;

typedef struct _Head
{
    int m_row, m_col;
    Node *link;
} Head;

void init(Head *);
void add(Head *, Element);

Head *add_matrix(Head mat_a, Head mat_b); // �� ��� ���ϴ� �Լ�
Head *sub_matrix(Head mat_a, Head mat_b); // �� ����� ������ �����ϴ� �Լ�
Head *matrix_transpose(Head h);           // ��ġ ����� ���ϴ� �Լ�
void display_matrix(Head *h);             // ��� ���·� ���
void display_list(Head *h);               // ����Ʈ �������� ���

void free_matrix(Head *);

// < test.txt -> scanf()�� �Է� �ޱ� ����
// > result.txt -> printf()�� ��� ����

int main()
{
    Head mat_a, mat_b;
    Head *mat_c, *mat_d, *mat_e;

    // ���� ������ �ذ��ϱ� ���� �ڵ� �߰�
    int row, col;
    scanf("%d %d", &row, &col);

    init(&mat_a);
    init(&mat_b);

    mat_c = NULL;

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

    display_matrix(&mat_a);
    printf("\n");
    display_list(&mat_a);
    printf("\n");
    display_matrix(&mat_b);
    printf("\n");
    display_list(&mat_b);

    mat_c = add_matrix(mat_a, mat_b);

    printf("\n");

    display_list(mat_c);
    display_matrix(mat_c);

    // ���� �Ҵ�� �޸� ��� ����
    free_matrix(&mat_a);
    free_matrix(&mat_b);
    free_matrix(mat_c);
    // free_matrix(mat_d);
    // free_matrix(mat_e);
    free(mat_c);
    mat_c = NULL;
    // free(mat_d);
    // mat_d = NULL;
    // free(mat_e);
    // mat_e = NULL;
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

    if (h->link == NULL)
    {
        h->link = newNode;
    }
    else
    {
        Node *last = h->link;
        while (last->link != NULL)
            last = last->link;
        last->link = newNode;
    }
}

Head *add_matrix(Head mat_a, Head mat_b)
{
    static Head mat_result;

    init(&mat_result);
    mat_result.m_row = mat_a.m_row;
    mat_result.m_col = mat_b.m_col;

    Node *aCur = mat_a.link;
    Node *bCur = mat_b.link;

    int aEndFlag = 0;
    int bEndFlag = 0;
    int addFlag = 0;

    for (int i = 0; i < mat_a.m_row; ++i)
    {
        for (int j = 0; j < mat_a.m_col; ++j)
        {
            if (aEndFlag == 0 && bEndFlag == 0)
            {
                if (aCur->data.row == i && aCur->data.col == j && bCur->data.row == i && bCur->data.col == j)
                {
                    Element element;
                    element.row = i;
                    element.col = i;
                    element.value = aCur->data.value + bCur->data.value;

                    add(&mat_result, element);

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
                    element.col = i;
                    element.value = aCur->data.value;

                    add(&mat_result, element);

                    aCur = aCur->link;
                }
            }
            if (bEndFlag == 0 && addFlag == 0)
            {
                if (bCur->data.row == i && bCur->data.col == j)
                {
                    Element element;
                    element.row = i;
                    element.col = i;
                    element.value = bCur->data.value;

                    add(&mat_result, element);

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

    return &mat_result;
}
Head *sub_matrix(Head mat_a, Head mat_b);
Head *matrix_transpose(Head h);

void display_matrix(Head *h)
{
    Node *cur = h->link;
    int endFlag = 0;
    for (int i = 0; i < h->m_row; ++i)
    {
        for (int j = 0; j < h->m_col; ++j)
        {
            if (cur->data.row == i && cur->data.col == j && endFlag == 0)
            {
                printf("1 ");
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

// �̰� �б��ʿ� ���׽��� ���� ������� �κп��� ���ͼ� �����ϸ�
// ���ϰ�, ���� ���� �ݹ� �����ҵ�?
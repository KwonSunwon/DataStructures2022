#include <stdio.h>
#include <stdlib.h>

#define PROB 3

#if PROB == 1

#elif PROB == 2

#elif PROB == 3

#define MAX_VERTICES 100

typedef int Element;

typedef struct Stack
{
    Element data[MAX_VERTICES];
    int top;

} Stack;
void init(Stack *);
void push(Stack *, int);
int pop(Stack *);
int is_empty(Stack *);
int is_full(Stack *);

typedef struct GraphNode
{
    int vertex;
    struct GraphNode *link;
} GraphNode;

typedef struct GraphType
{
    int n; // ������ ����
    GraphNode *adj_list[MAX_VERTICES];
} GraphType;

void graph_init(GraphType *);
void set_vertex(GraphType *, int);
void insert_edge(GraphType *, int, int);
int topo_sort(GraphType *);
void delete_graph(GraphType *);

int main(void)
{
    GraphType g;
    graph_init(&g);
    // test data 1
    /*
    set_vertex(&g, 6);
    insert_edge(&g, 0, 2);
    insert_edge(&g, 0, 3);
    insert_edge(&g, 1, 3);
    insert_edge(&g, 1, 4);
    insert_edge(&g, 2, 3);
    insert_edge(&g, 2, 5);
    insert_edge(&g, 3, 5);
    insert_edge(&g, 4, 5);
    */
    // test data 2
    set_vertex(&g, 8);
    insert_edge(&g, 0, 1);
    insert_edge(&g, 1, 2);
    insert_edge(&g, 1, 3);
    insert_edge(&g, 1, 4);
    insert_edge(&g, 2, 7);
    insert_edge(&g, 3, 6);
    insert_edge(&g, 4, 5);
    insert_edge(&g, 4, 6);
    insert_edge(&g, 5, 7);
    insert_edge(&g, 6, 7);
    //���� ����
    topo_sort(&g);
    // ���� �޸� ��ȯ �ڵ� ����
    //delete_graph(&g);
    return 0;
}

void graph_init(GraphType *g)
{
    g->n = 0;
    for (int i = 0; i < MAX_VERTICES; ++i)
        g->adj_list[i] = NULL;
}
void set_vertex(GraphType *g, int size)
{
    g->n = size;
    for (int i = 0; i < size; ++i)
    {
        GraphNode *new = (GraphNode *)malloc(sizeof(GraphNode));
        new->vertex = i;
        new->link = NULL;
        g->adj_list[i] = new;
    }
}
void insert_edge(GraphType *g, int from, int to)
{
    GraphNode *new = (GraphNode *)malloc(sizeof(GraphNode));
    new->vertex = to;
    new->link = NULL;

    if (g->adj_list[from]->link == NULL)
        g->adj_list[from]->link = new;
    else
    {
        GraphNode *pos = g->adj_list[from]->link;
        while (pos->link != NULL)
            pos = pos->link;
        pos->link = new;
    }
}

int topo_sort(GraphType *g)
{
    int i;
    Stack s;
    GraphNode *node;
    int *inDegree = (int *)malloc(g->n * sizeof(int));
    for (i = 0; i < g->n; ++i)
        inDegree[i] = 0;
    for (i = 0; i < g->n; ++i)
    {
        node = g->adj_list[i]; //���� i���� ������ ������
        while (node != NULL)
        {
            inDegree[node->vertex]++;
            node = node->link;
        }
    }
    init(&s);
    for (i = 0; i < g->n; i++)
    {
        if (inDegree[i] == 0)
            push(&s, i);
    }
    // ���� ������ ����
    while (!is_empty(&s))
    {
        int w;
        w = pop(&s);
        printf("���� %d ->", w); //���� ���
        node = g->adj_list[w];   //�� ������ ���� ������ ����
        while (node != NULL)
        {
            int u = node->vertex;
            inDegree[u]--; //���� ������ ����
            if (inDegree[u] == 0)
                push(&s, u);
            node = node->link; // ���� ����
        }
    }
    free(inDegree);
    printf("\n");
    return (i == g->n); // ��ȯ���� 1�̸� ����, 0�̸� ����
}

void init(Stack *s)
{
    s->top = -1;
}
void push(Stack *s, int e)
{
    if (!is_full(s))
        s->data[++s->top] = e;
}
int pop(Stack *s)
{
    if (!is_empty(s))
        return s->data[s->top--];
    else
        return 0;
}
int is_empty(Stack *s)
{
    if (s->top == -1)
        return 1;
    else
        return 0;
}
int is_full(Stack *s)
{
    if (s->top == MAX_VERTICES)
        return 1;
    else
        return 0;
}

#endif
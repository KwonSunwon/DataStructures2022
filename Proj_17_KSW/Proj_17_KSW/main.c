#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50
#define MAX_STACK 100
#define MAX_QUEUE 100

int visited[MAX_VERTICES];

#define PROB 2

#if PROB == 1

typedef struct GraphType
{
    int n; // 정점의 개수
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

#elif PROB == 2

typedef struct GraphNode
{
    int vertex;
    struct GraphNode *link;
} GraphNode;

typedef struct GraphType
{
    int n; // 정점의 개수
    GraphNode *adj_list[MAX_VERTICES];
} GraphType;

#endif

typedef int Element;

typedef struct Stack
{
    Element data[MAX_STACK];
    int top;
} Stack;

void stack_init(Stack *);
void push(Stack *, Element);
Element pop(Stack *);
int stack_is_full(Stack *);
int stack_is_empty(Stack *);

typedef struct Queue
{
    Element data[MAX_QUEUE];
    int front, rear;
} Queue;

void queue_init(Queue *);
void enqueue(Queue *, Element);
Element dequeue(Queue *);
int queue_is_full(Queue *);
int queue_is_empty(Queue *);

#if PROB == 1

void init(GraphType *);
void insert_vertex(GraphType *, int);
void set_vertex(GraphType *, int);
void insert_edge(GraphType *, int, int);
void dfs_mat(GraphType *, int);
void bfs_mat(GraphType *, int);

int main()
{

    GraphType *g;
    g = (GraphType *)malloc(sizeof(GraphType));
    init(g);
    set_vertex(g, 11);
    insert_edge(g, 0, 1);
    insert_edge(g, 0, 2);
    insert_edge(g, 0, 3);
    insert_edge(g, 1, 2);
    insert_edge(g, 1, 3);
    insert_edge(g, 2, 3);
    insert_edge(g, 2, 4);
    insert_edge(g, 4, 5);
    insert_edge(g, 4, 7);
    insert_edge(g, 4, 8);
    insert_edge(g, 5, 6);
    insert_edge(g, 6, 7);
    insert_edge(g, 6, 10);
    insert_edge(g, 7, 9);
    insert_edge(g, 7, 10);
    insert_edge(g, 8, 9);

    for (int i = 0; i < MAX_VERTICES; ++i)
        visited[i] = 0;
    printf("깊이 우선 탐색\n");
    dfs_mat(g, 0);
    printf("\n");

    for (int i = 0; i < MAX_VERTICES; ++i)
        visited[i] = 0;
    printf("너비 우선 탐색\n");
    bfs_mat(g, 0);
    printf("\n");

    free(g);
}

void init(GraphType *g)
{
    int row, col;
    g->n = 0;
    for (row = 0; row < MAX_VERTICES; ++row)
        for (col = 0; col < MAX_VERTICES; ++col)
            g->adj_mat[row][col] = 0;
}

void set_vertex(GraphType *g, int size)
{
    g->n = size;
}

void insert_edge(GraphType *g, int from, int to)
{
    if (from >= g->n || to >= g->n)
        return;

    g->adj_mat[from][to] = 1;
    g->adj_mat[to][from] = 1;
}

void dfs_mat(GraphType *g, int visit)
{
    visited[visit] = 1;
    printf("[%d] 방문 -> ", visit);
    for (int i = 0; i < g->n; ++i)
        if (g->adj_mat[visit][i] && !visited[i])
            dfs_mat(g, i);
}

void bfs_mat(GraphType *g, int visit)
{
    Queue q;
    queue_init(&q);

    visited[visit] = 1;
    printf("[%d] 방문 -> ", visit);
    enqueue(&q, visit);
    while (!queue_is_empty(&q))
    {
        visit = dequeue(&q);
        for (int i = 0; i < g->n; ++i)
            if (g->adj_mat[visit][i] && !visited[i])
            {
                visited[i] = 1;
                printf("[%d] 방문 -> ", i);
                enqueue(&q, i);
            }
    }
}

#elif PROB == 2

void init(GraphType *);
void insert_vertex(GraphType *, int);
void set_vertex(GraphType *, int);
void insert_edge(GraphType *, int, int);
void dfs_list(GraphType *, int);
void bfs_list(GraphType *, int);

int main()
{
    GraphType *g;
    g = (GraphType *)malloc(sizeof(GraphType));
    init(g);
    set_vertex(g, 11);
    insert_edge(g, 0, 1);
    insert_edge(g, 0, 2);
    insert_edge(g, 0, 3);
    insert_edge(g, 1, 2);
    insert_edge(g, 1, 3);
    insert_edge(g, 2, 3);
    insert_edge(g, 2, 4);
    insert_edge(g, 4, 5);
    insert_edge(g, 4, 7);
    insert_edge(g, 4, 8);
    insert_edge(g, 5, 6);
    insert_edge(g, 6, 7);
    insert_edge(g, 6, 10);
    insert_edge(g, 7, 9);
    insert_edge(g, 7, 10);
    insert_edge(g, 8, 9);

    int visited[MAX_VERTICES];

    for (int i = 0; i < MAX_VERTICES; ++i)
        visited[i] = 0;
    printf("깊이 우선 탐색\n");
    dfs_list(g, 0);
    printf("\n");

        printf("너비 우선 탐색\n");
    bfs_list(g, 0);
    printf("\n");

    free(g);
}

void init(GraphType *g)
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

void dfs_list(GraphType *g, int visit)
{
    GraphNode *pos;
    visited[visit] = 1;
    printf("[%d] 방문 -> ", visit);
    for (pos = g->adj_list[visit]; pos; pos = pos->link)
        if (!visited[pos->vertex])
            dfs_list(g, pos->vertex);
}

void bfs_list(GraphType *g, int visit)
{
    for (int i = 0; i < MAX_VERTICES; ++i)
        visited[i] = 0;

    GraphNode *pos;
    Queue q;
    queue_init(&q);

    visited[visit] = 1;
    printf("[%d] 방문 -> ", visit);
    enqueue(&q, visit);
    while (!queue_is_empty(&q))
    {
        visit = dequeue(&q);
        for (pos = g->adj_list[visit]; pos; pos = pos->link)
            if (!visited[pos->vertex])
            {
                visited[pos->vertex] = 1;
                printf("[%d] 방문 -> ", pos->vertex);
                enqueue(&q, pos->vertex);
            }
    }
}

#endif

// Stack
void stack_init(Stack *s)
{
    s->top = -1;
}
void push(Stack *s, Element e)
{
    if (stack_is_full(s))
        printf("Stack is full\n");
    else
        s->data[++s->top] = e;
}
Element pop(Stack *s)
{
    if (stack_is_empty(s))
        printf("Stack is empty\n");
    else
        return s->data[s->top--];
}
int stack_is_full(Stack *s)
{
    if (s->top == MAX_STACK)
        return 1;
    else
        return 0;
}
int stack_is_empty(Stack *s)
{
    if (s->top == -1)
        return 1;
    else
        return 0;
}

// Queue
void queue_init(Queue *q)
{
    q->front = 0;
    q->rear = 0;
}
void enqueue(Queue *q, Element e)
{
    if (queue_is_full(q))
        printf("Queue is full\n");
    else
    {
        q->rear = (q->rear + 1) % MAX_QUEUE;
        q->data[q->rear] = e;
    }
}
Element dequeue(Queue *q)
{
    if (queue_is_empty(q))
        printf("Queue is empty\n");
    else
    {
        q->front = (q->front + 1) % MAX_QUEUE;
        return q->data[q->front];
    }
}
int queue_is_full(Queue *q)
{
    if ((q->rear + 1) % MAX_QUEUE == q->front)
        return 1;
    else
        return 0;
}
int queue_is_empty(Queue *q)
{
    if (q->front == q->rear)
        return 1;
    else
        return 0;
}
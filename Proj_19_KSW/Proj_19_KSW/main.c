#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define PROB 3

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

#if PROB == 1 || PROB == 2

#define TRUE 1
#define FALSE 0
#define INF 10000 /* 무한대 (연결이 없는 경우) */

typedef struct GraphType
{
    int n; // 정점의 개수
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

#endif

#if PROB == 1

int distance[MAX_VERTICES]; /* 시작정점으로부터의 최단경로 거리 */
int found[MAX_VERTICES];    /* 방문한 정점 표시 */
int path[MAX_VERTICES];     /* 경유 노드 */

int choose(int[], int, int[]);
void shortest_path(GraphType *, int);
void print_path(int, int);

void print_status(GraphType *);

int main()
{
    /*
    // test data 1
    GraphType g = {7,
                   {{0, 7, INF, INF, 3, 10, INF},
                    {7, 0, 4, 10, 2, 6, INF},
                    {INF, 4, 0, 2, INF, INF, INF},
                    {INF, 10, 2, 0, 11, 9, 4},
                    {3, 2, INF, 11, 0, INF, 5},
                    {10, 6, INF, 9, INF, 0, INF},
                    {INF, INF, INF, 4, 5, INF, 0}}};
    */

    // 방향성 그래프에도 적용 가능
    /*
    // test data 2
    GraphType g = {6,
                   {{0, 50, 45, 10, INF, INF},
                    {INF, 0, 10, 15, INF, INF},
                    {INF, INF, 0, INF, 30, INF},
                    {20, INF, INF, 0, 15, INF},
                    {INF, 20, 35, INF, 0, INF},
                    {INF, INF, INF, INF, 3, 0}}};
    */
    /*
    // test data 3
    GraphType g = {7,
                   {{0, 7, INF, 5, INF, INF, INF},
                    {7, 0, 8, 9, 7, INF, INF},
                    {INF, 8, 0, INF, 5, INF, INF},
                    {5, 9, INF, 0, 15, 6, INF},
                    {INF, 7, 5, 15, 0, 8, 9},
                    {INF, INF, INF, 6, 8, 0, 11},
                    {INF, INF, INF, INF, 9, 11, 0}}};
    */
    GraphType g = {7,
                   {
                       {0, 7, INF, INF, 3, 10, INF},
                       {7, 0, 4, 10, 2, 6, INF},
                       {INF, 4, 0, 2, INF, INF, INF},
                       {INF, 10, 2, 0, 11, 9, 4},
                       {3, 2, INF, INF, 0, INF, 5},
                       {10, 6, INF, 9, INF, 0, INF},
                       {INF, INF, INF, 4, 5, INF, 0},
                   }};

    shortest_path(&g, 0);
    printf("\n정점 %d에서 정점 %d까지의 경로 : ", 0, 3);
    print_path(0, 3);
    printf("\n");
}

int choose(int distance[], int n, int found[])
{
    int min, minPos;
    min = INT_MAX;
    minPos = -1;
    for (int i = 0; i < n; ++i)
        if (distance[i] < min && !found[i])
        {
            min = distance[i];
            minPos = i;
        }
    return minPos;
}
void shortest_path(GraphType *g, int start)
{
    int u, w;
    for (int i = 0; i < g->n; ++i)
    {
        distance[i] = g->weight[start][i];
        found[i] = FALSE;
        path[i] = start;
    }
    found[start] = TRUE;
    distance[start] = 0;
    for (int i = 0; i < g->n - 1; ++i)
    {
        printf("STEP %d: ", i + 1);
        print_status(g);
        printf("\n");
        u = choose(distance, g->n, found);
        found[u] = TRUE;
        for (int w = 0; w < g->n; ++w)
            if (!found[w])
                if (distance[u] + g->weight[u][w] < distance[w])
                {
                    distance[w] = distance[u] + g->weight[u][w];
                    path[w] = u;
                }
        if (distance[u] == INF)
            path[u] = -1;
    }
}

void print_path(int start, int end)
{
    Stack s;
    init(&s);

    push(&s, end);
    int prev = path[end];
    while (prev != start)
    {
        if (prev == -1)
        {
            printf("경로 없음\n");
            return 0;
        }
        push(&s, prev);
        prev = path[prev];
    }
    int from, to;
    from = start;
    while (!is_empty(&s))
    {
        to = pop(&s);
        printf("<%d->%d> ", from, to);
        from = to;
    }
}

void print_status(GraphType *g)
{
    printf("distance: ");
    for (int i = 0; i < g->n; ++i)
    {
        if (distance[i] != INF)
            printf("%d\t", distance[i]);
        else
            printf("*\t");
    }
    printf("\n");
    printf("\tfound:    ");
    for (int i = 0; i < g->n; ++i)
        printf("%d\t", found[i]);
    printf("\n");
}

#elif PROB == 2

void floyd(GraphType *);
void printA(GraphType *);
void print_path(int[][MAX_VERTICES], int, int);
void search_path(int, int);

int A[MAX_VERTICES][MAX_VERTICES];
int path[MAX_VERTICES][MAX_VERTICES];
Stack s;

int main(void)
{
    GraphType g = {7,
                   {
                       {0, 7, INF, INF, 3, 10, INF},
                       {7, 0, 4, 10, 2, 6, INF},
                       {INF, 4, 0, 2, INF, INF, INF},
                       {INF, 10, 2, 0, 11, 9, 4},
                       {3, 2, INF, INF, 0, INF, 5},
                       {10, 6, INF, 9, INF, 0, INF},
                       {INF, INF, INF, 4, 5, INF, 0},
                   }};

    // test data 1
    // GraphType g = {7,
    //                {{0, 7, INF, INF, 3, 10, INF},
    //                 {7, 0, 4, 10, 2, 6, INF},
    //                 {INF, 4, 0, 2, INF, INF, INF},
    //                 {INF, 10, 2, 0, 11, 9, 4},
    //                 {3, 2, INF, 11, 0, INF, 5},
    //                 {10, 6, INF, 9, INF, 0, INF},
    //                 {INF, INF, INF, 4, 5, INF, 0}}};

    // 방향성 그래프에도 적용 가능
    // test data 2
    // GraphType g = {6,
    //                {{0, 50, 45, 10, INF, INF},
    //                 {INF, 0, 10, 15, INF, INF},
    //                 {INF, INF, 0, INF, 30, INF},
    //                 {20, INF, INF, 0, 15, INF},
    //                 {INF, 20, 35, INF, 0, INF},
    //                 {INF, INF, INF, INF, 3, 0}}};

    /*
    // test data 3
    GraphType g = {7,
                   {{0, 7, INF, 5, INF, INF, INF},
                    {7, 0, 8, 9, 7, INF, INF},
                    {INF, 8, 0, INF, 5, INF, INF},
                    {5, 9, INF, 0, 15, 6, INF},
                    {INF, 7, 5, 15, 0, 8, 9},
                    {INF, INF, INF, 6, 8, 0, 11},
                    {INF, INF, INF, INF, 9, 11, 0}}};
    */
    floyd(&g);
    printf("\n정점 %d에서 정점 %d까지의 경로 : ", 0, 5);
    print_path(path, 0, 6); // 정점 0에서 정점 3으로 가는 최단경로 출력

    // printf("\n정점 %d에서 정점 %d까지의 경로 : ", 0, 5);
    // print_path(path, 0, 5); // 정점 0에서 정점 3으로 가는 최단경로 출력
    printf("\n");
    return 0;
}

void floyd(GraphType *g)
{
    int i, j;
    for (i = 0; i < g->n; ++i)
        for (int j = 0; j < g->n; ++j)
        {
            A[i][j] = g->weight[i][j];
            path[i][j] = 0;
        }
    printA(g);
    for (int k = 0; k < g->n; ++k)
    {
        for (i = 0; i < g->n; ++i)
            for (j = 0; j < g->n; ++j)
                if (A[i][k] + A[k][j] < A[i][j])
                {
                    A[i][j] = A[i][k] + A[k][j];
                    path[i][j] = k;
                }
        printA(g);
    }
    for (i = 0; i < g->n; ++i)
        for (j = 0; j < g->n; ++j)
        {
            if (A[i][j] == INF)
                path[i][j] = -1;
        }
}

void print_path(int path[][MAX_VERTICES], int start, int end)
{
    init(&s);
    push(&s, start);
    search_path(start, end);
    push(&s, end);

    for (int i = 0; i < s.top; ++i)
        if (s.data[i] == -1)
        {
            printf("경로 없음\n");
            return;
        }
    printf("%d", start);
    for (int i = 1; i < s.top; ++i)
        printf("->%d", s.data[i]);
    printf("->%d\n", end);
}

void search_path(int start, int end)
{
    if (path[start][end] != 0)
    {
        search_path(start, path[start][end]);
        push(&s, path[start][end]);
        search_path(path[start][end], end);
    }
}

void printA(GraphType *g)
{
    printf("=====================================================\n");
    for (int i = 0; i < g->n; ++i)
    {
        for (int j = 0; j < g->n; ++j)
        {
            if (A[i][j] != INF)
                printf("%d\t", A[i][j]);
            else
                printf("*\t");
        }
        printf("\n");
    }
    printf("=====================================================\n");
}

#elif PROB == 3

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

    set_vertex(&g, 6);
    insert_edge(&g, 0, 2);
    insert_edge(&g, 0, 3);
    insert_edge(&g, 1, 3);
    insert_edge(&g, 1, 4);
    insert_edge(&g, 2, 3);
    insert_edge(&g, 2, 5);
    insert_edge(&g, 3, 5);
    insert_edge(&g, 4, 5);
    /*
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
    */
    //위상 정렬
    topo_sort(&g);
    // 동적 메모리 반환 코드 생략
    delete_graph(&g);
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
}
void insert_edge(GraphType *g, int from, int to)
{
    GraphNode *new = (GraphNode *)malloc(sizeof(GraphNode));
    new->vertex = to;
    new->link = NULL;

    if (g->adj_list[from] == NULL)
        g->adj_list[from] = new;
    else
    {
        GraphNode *pos = g->adj_list[from];
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
        node = g->adj_list[i]; //정점 i에서 나오는 간선들
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
    // 위상 순서를 생성
    while (!is_empty(&s))
    {
        int w;
        w = pop(&s);
        printf("정점 %d ->", w); //정점 출력
        node = g->adj_list[w];   //각 정점의 진입 차수를 변경
        while (node != NULL)
        {
            int u = node->vertex;
            inDegree[u]--; //진입 차수를 감소
            if (inDegree[u] == 0)
                push(&s, u);
            node = node->link; // 다음 정점
        }
    }
    free(inDegree);
    printf("\n");
    return (i == g->n); // 반환값이 1이면 성공, 0이면 실패
}

void delete_graph(GraphType *g)
{
    GraphNode *del, *pos;
    for (int i = 0; i < g->n; ++i)
    {
        pos = g->adj_list[i];
        while (pos != NULL)
        {
            del = pos;
            pos = pos->link;
            free(del);
        }
    }
}

#endif

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
#include <stdio.h>
#include <stdlib.h>

#define PROB 2

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000

#if PROB == 1

int parent[MAX_VERTICES];

void set_init(int);
int set_find(int);
void set_union(int, int);

typedef struct Edge
{ // 간선을 나타내는 구조체
    int start, end, weight;
} Edge;

typedef struct GraphType
{
    int en; // 간선의 개수
    int vn; // 정점의 개수
    struct Edge edges[2 * MAX_VERTICES];
} GraphType;

void graph_init(GraphType *);
void set_nodes(GraphType *, int);
void insert_edge(GraphType *, int, int, int);

void kruskal(GraphType *);

int main()
{
    GraphType *g;
    g = (GraphType *)malloc(sizeof(GraphType));
    graph_init(g);

    // test data 1
    set_nodes(g, 7);
    insert_edge(g, 0, 1, 29);
    insert_edge(g, 1, 2, 16);
    insert_edge(g, 2, 3, 12);
    insert_edge(g, 3, 4, 22);
    insert_edge(g, 4, 5, 27);
    insert_edge(g, 5, 0, 10);
    insert_edge(g, 6, 1, 15);
    insert_edge(g, 6, 3, 18);
    insert_edge(g, 6, 4, 25);

    kruskal(g);
    free(g);
}

void set_init(int n)
{
    for (int i = 0; i < n; ++i)
        parent[i] = -1;
}
int set_find(int curr)
{
}
void set_union(int a, int b);

void graph_init(GraphType *g)
{
    g->en = 0;
    g->vn = 0;
    for (int i = 0; i < 2 * MAX_VERTICES; ++i)
        g->edges[i] = (Edge){0, 0, INF};
}
void set_nodes(GraphType *g, int vn)
{
    g->vn = vn;
}
void insert_edge(GraphType *g, int start, int edge, int weight)
{
    g->edges[g->en++] = (Edge){start, edge, weight};
}

void kruskal(GraphType *g)
{
}

#elif PROB == 2

#define N_NODE 7

typedef struct GraphType
{
    int n; // 정점의 개수
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int selected[MAX_VERTICES];
int distance[MAX_VERTICES];

int main(void)
{
    int i;
    // test data1
    GraphType g = {N_NODE,
                   {{0, 29, INF, INF, INF, 10, INF},
                    {29, 0, 16, INF, INF, INF, 15},
                    {INF, 16, 0, 12, INF, INF, INF},
                    {INF, INF, 12, 0, 22, INF, 18},
                    {INF, INF, INF, 22, 0, 27, 25},
                    {10, INF, INF, INF, 27, 0, INF},
                    {INF, 15, INF, 18, 25, INF, 0}}};
    // test data2
    /*
    GraphType g = { N_NODE,
    { { 0, 10, INF, 6, INF, INF, INF, 1 },
    { 10, 0, 4, INF, INF, 2, INF, INF },
    { INF, 4, 0, 11, INF, 7, INF, INF },
    { 6, INF, 11, 0, INF, INF, INF, 3 },
    { INF, INF, INF, INF, 0, 5, INF, 8},
    { INF, 2, 7, INF, 5, 0, 9, INF },
    { INF, INF, INF, INF, INF, 9, 0, 12 },
    { 1, INF, INF, 3, 8, INF, 12, 0 }
    }
    };
    */
    prim(&g, 0);
}

#endif
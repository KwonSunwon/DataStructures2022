#include <stdio.h>
#include <stdlib.h>

#define PROB 1

typedef struct WORLD_COORDINATE
{
    int x;
    int y;
    int z;
} Element;

#if PROB == 1

typedef struct STACKNODE
{
    Element data;
    struct STACKNODE *link;
} StackNode;

typedef struct
{
    StackNode *top;
} LinkedNode;

void init(LinkedNode *);
int is_empty(LinkedNode *);
int is_full(LinkedNode *);
void push(LinkedNode *, Element);
Element pop(LinkedNode *);
Element peek(LinkedNode *);
void print_stack(LinkedNode *);
void clear_stack(LinkedNode *);

int main()
{
    LinkedNode s;
    Element item;

    init(&s);
    print_stack(&s);
    item.x = 1;
    item.y = 1;
    item.z = 1;
    printf("Push item\n");
    push(&s, item);
    print_stack(&s);
    item.x = 2;
    item.y = 2;
    item.z = 2;
    printf("Push item\n");
    push(&s, item);
    print_stack(&s);
    item.x = 3;
    item.y = 3;
    item.z = 3;
    printf("Push item\n");
    push(&s, item);
    print_stack(&s);
    item.x = 4;
    item.y = 4;
    item.z = 4;
    printf("Push item\n");
    push(&s, item);
    print_stack(&s);
    printf("PoP item\n");
    item = pop(&s);
    printf("PoP된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
    print_stack(&s);
    printf("PoP item\n");
    item = pop(&s);
    printf("PoP된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
    print_stack(&s);
    printf("PoP item\n");
    item = pop(&s);
    printf("PoP된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
    print_stack(&s);
    printf("PoP item\n");
    item = pop(&s);
    printf("PoP된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
    print_stack(&s);
    printf("PoP item\n");
    item = pop(&s);
    printf("PoP data : (%d, %d, %d) \n", item.x, item.y, item.z);
    print_stack(&s);
    printf("PoP item\n");
    item = pop(&s);
    printf("PoP된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
    print_stack(&s);

    clear_stack(&s);
}

void init(LinkedNode *s)
{
    s->top = NULL;
}
int is_empty(LinkedNode *s)
{
    if (s->top == NULL)
        return 1;
    else
        return 0;
}
int is_full(LinkedNode *s)
{
    return 0;
}
void push(LinkedNode *s, Element e)
{
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    if (newNode == NULL)
    {
        printf("Dynamic allocatoin failed!");
        exit(-1);
    }
    newNode->data = e;
    newNode->link = s->top;
    s->top = newNode;
}
Element pop(LinkedNode *s)
{
    Element e = {INT_MIN, INT_MIN, INT_MIN};

    if (is_empty(s))
    {
        printf("스택이 비어있음\n");
        return e;
    }

    e = s->top->data;

    StackNode *popNode;
    popNode = s->top;
    s->top = popNode->link;

    free(popNode);

    return e;
}
Element peek(LinkedNode *s)
{
    Element e;
    e = s->top->data;
    return e;
}
void print_stack(LinkedNode *s)
{
    printf("=======스택 내용=======\n");
    if (is_empty(s))
    {
        printf("< NULL > <--- TOP\n");
        printf("=======================\n");
        return;
    }

    StackNode *pos = s->top;
    printf("<%d, %d, %d>", pos->data.x, pos->data.y, pos->data.z);
    printf(" <--- TOP\n");

    while (1)
    {
        if (pos->link == NULL)
        {
            printf("=======================\n");
            return;
        }
        pos = pos->link;
        printf("<%d, %d, %d>\n", pos->data.x, pos->data.y, pos->data.z);
    }
}
void clear_stack(LinkedNode *s)
{
    if (is_empty(s))
        return;

    StackNode *delNode;
    delNode = s->top;
    while (s->top != NULL)
    {
        s->top = delNode->link;
        free(delNode);
        delNode = s->top;
    }
}

#elif PROB == 2

typedef struct QUEUENODE
{
    Element data;
    struct QUEUENODE *link;
} QueueNode;

typedef struct
{
    QueueNode *front;
    QueueNode *rear;
} LinkedQueue;

void init(LinkedQueue *);
int is_empty(LinkedQueue *);
int is_full(LinkedQueue *);
void enqueue(LinkedQueue *, Element);
Element dequeue(LinkedQueue *);
void print_queue(LinkedQueue *);
void clear_queue(LinkedQueue *);

int main()
{
    LinkedQueue queue;
    Element item;

    init(&queue); // 큐 초기화
    print_queue(&queue);
    printf("enqueue item \n");
    item.x = 1, item.y = 1, item.z = 1;
    enqueue(&queue, item);
    print_queue(&queue);
    printf("enqueue item \n");
    item.x = 2, item.y = 2, item.z = 2;
    enqueue(&queue, item);
    print_queue(&queue);
    printf("enqueue item \n");
    item.x = 3, item.y = 3, item.z = 3;
    enqueue(&queue, item);
    print_queue(&queue);
    printf("enqueue item \n");
    item.x = 4, item.y = 4, item.z = 4;
    enqueue(&queue, item);
    print_queue(&queue);
    printf("enqueue item \n");
    item.x = 5, item.y = 5, item.z = 5;
    enqueue(&queue, item);
    print_queue(&queue);
    printf("dequeue item\n");
    item = dequeue(&queue);
    printf("Dequeue된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
    print_queue(&queue);
    printf("dequeue item\n");
    item = dequeue(&queue);
    printf("Dequeue된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
    print_queue(&queue);
    printf("dequeue item\n");
    item = dequeue(&queue);
    printf("Dequeue된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
    print_queue(&queue);
    printf("dequeue item\n");
    item = dequeue(&queue);
    printf("Dequeue된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
    print_queue(&queue);
    printf("dequeue item\n");
    item = dequeue(&queue);
    printf("Dequeue된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
    print_queue(&queue);
    printf("dequeue item\n");
    item = dequeue(&queue);
    printf("Dequeue된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
    print_queue(&queue);

    clear_queue(&queue);
}

void init(LinkedQueue *q)
{
    q->front = NULL;
    q->rear = NULL;
}
int is_empty(LinkedQueue *q)
{
    if (q->front == NULL && q->rear == NULL)
        return 1;
    else
        return 0;
}
int is_full(LinkedQueue *q)
{
    return 1;
}
void enqueue(LinkedQueue *q, Element e)
{
    QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
    if (newNode == NULL)
    {
        printf("Dynamic allocatoin failed!");
        exit(-1);
    }

    newNode->data = e;
    newNode->link = NULL;

    if (is_empty(q))
    {
        q->front = newNode;
        q->rear = newNode;
    }
    else
    {
        q->rear->link = newNode;
        q->rear = newNode;
    }
}
Element dequeue(LinkedQueue *q)
{
    Element e = {INT_MIN, INT_MIN, INT_MIN};
    if (is_empty(q))
    {
        printf("큐가 비어있음\n");
        return e;
    }

    QueueNode *deNode = q->front;
    q->front = deNode->link;
    e = deNode->data;
    free(deNode);

    if (q->front == NULL)
        q->rear = NULL;

    return e;
}
void print_queue(LinkedQueue *q)
{
    printf("========큐 내용========\n");
    if (is_empty(q))
    {
        printf("< NULL > <--- Front, Rear\n");
        printf("=======================\n");
        return;
    }

    if (q->front == q->rear)
    {
        printf("<%d, %d, %d> <--- Front, Rear\n", q->front->data.x, q->front->data.y, q->front->data.z);
        printf("=======================\n");
        return;
    }

    QueueNode *pos = q->front;

    printf("<%d, %d, %d> <--- Front\n", pos->data.x, pos->data.y, pos->data.z);
    pos = pos->link;

    while (1)
    {
        if (pos == q->rear)
            break;
        printf("<%d, %d, %d>\n", pos->data.x, pos->data.y, pos->data.z);
        pos = pos->link;
    }

    printf("<%d, %d, %d> <--- Rear\n", pos->data.x, pos->data.y, pos->data.z);
    printf("=======================\n");
}
void clear_queue(LinkedQueue *q)
{
    if (is_empty(q))
        return;

    if (q->front == q->rear)
    {
        free(q->front);
        q->front = NULL;
        q->rear = NULL;
        return;
    }

    QueueNode *delNode = q->front;

    while (q->front != q->rear)
    {
        q->front = delNode->link;
        free(delNode);
    }
    free(q->front);
    q->front = NULL;
    q->rear = NULL;
}

#endif
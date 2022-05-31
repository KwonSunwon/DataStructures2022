#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 1000

typedef struct AVLNode
{
    int key;
    struct AVLNode *left, *right;
} AVLNode;

typedef struct _qData
{
    AVLNode *node;
    int level;
} qData;

typedef struct _Queue
{
    qData data[MAX_QUEUE_SIZE];
    int front;
    int rear;
} Queue;

AVLNode *AVL_insert(AVLNode *, int);
void level_order(AVLNode *);

int get_balance(AVLNode *);
int get_height(AVLNode *);

AVLNode *rotate_right(AVLNode *);
AVLNode *rotate_left(AVLNode *);

int main()
{
    AVLNode *root = NULL;

    printf("Insert %d\n", 5);
    root = AVL_insert(root, 5);
    printf("Insert %d\n", 4);
    root = AVL_insert(root, 4);
    printf("Insert %d\n", 3);
    root = AVL_insert(root, 3);
    level_order(root);
    printf("Insert %d\n", 2);
    root = AVL_insert(root, 2);
    level_order(root);
    printf("Insert %d\n", 1);
    root = AVL_insert(root, 1);
    level_order(root);
    printf("Remove %d\n", 5);
    root = AVL_remove(root, 5);
    level_order(root);
    printf("Insert %d\n", 6);
    root = AVL_insert(root, 6);
    level_order(root);
    printf("Insert %d\n", 7);
    root = AVL_insert(root, 7);
    level_order(root);
    printf("Insert %d\n", 8);
    root = AVL_insert(root, 8);
    level_order(root);
    printf("Insert %d\n", 9);
    root = AVL_insert(root, 9);
    level_order(root);
    printf("Insert %d\n", 10);
    root = AVL_insert(root, 10);
    level_order(root);
    printf("Insert %d\n", 15);
    root = AVL_insert(root, 15);
    level_order(root);
    printf("Insert %d\n", 14);
    root = AVL_insert(root, 14);
    level_order(root);
    printf("Insert %d\n", 13);
    root = AVL_insert(root, 13);
    level_order(root);
    printf("Insert %d\n", 12);
    root = AVL_insert(root, 12);
    level_order(root);
    printf("Insert %d\n", 11);
    root = AVL_insert(root, 11);
    level_order(root);
    printf("Insert %d\n", 12);
    root = AVL_insert(root, 12);
    level_order(root);
    printf("Remove %d\n", 11);
    root = AVL_remove(root, 11);
    level_order(root);
    printf("Remove %d\n", 9);
    root = AVL_remove(root, 9);
    level_order(root);
}

AVLNode *AVL_insert(AVLNode *root, int key)
{
    AVLNode *new = (AVLNode *)malloc(sizeof(AVLNode));
    new->key = key;
    new->left = NULL;
    new->right = NULL;

    AVLNode *pos = root;
    if (!root)
        root = new;
    else
    {
        while (1)
        {
            if (pos->key > key)
            {
                if (!pos->left)
                {
                    pos->left = new;
                    break;
                }
                pos = pos->left;
            }
            else if (pos->key < key)
            {
                if (!pos->right)
                {
                    pos->right = new;
                    break;
                }
                pos = pos->right;
            }
            else if (pos->key == key)
            {
                printf("중복된 데이터\n");
                free(new);
                return root;
            }
            push(/*stack*/, pos);
        }
    }

    while (stack_is_empty(/*stack*/))
    {
        pos = pop(/*stack*/);
        int balanceFactor = get_balance(pos);
        if(balanceFactor > 1 && )
    }
    return root;
}

int get_balance(AVLNode *node)
{
    return get_height(node->left) - get_height(node->right);
}

int get_height(AVLNode *node)
{
    int height = 0;
    if (node != NULL)
        height = 1 + max(get_height(node->left), get_height(node->right));
    return height;
}

void level_order(AVLNode *root)
{
    Queue q;
    queue_init(&q);

    Queue out;
    queue_init(&out);

    qData data = {root, 1};
    enqueue(&q, data);

    while (!is_empty(&q))
    {
        data = dequeue(&q);

        enqueue(&out, data);

        data.level++;
        if (data.node->left)
            enqueue(&q, (qData){data.node->left, data.level});
        if (data.node->right)
            enqueue(&q, (qData){data.node->right, data.level});
    }

    int level = 1;

    printf("Level %d : ", level);
    while (!is_empty(&out))
    {
        data = dequeue(&out);
        if (level != data.level)
        {
            printf("\nLevel %d : ", ++level);
            printf("[%d] ", data.node->key);
            continue;
        }
        printf("[%d] ", data.node->key);
    }
}

void queue_init(Queue *q)
{
    q->front = -1;
    q->rear = -1;
}

void enqueue(Queue *q, qData item)
{
    if (is_full(q))
    {
        printf("Queue is full");
        return;
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

qData dequeue(Queue *q)
{
    if (is_empty(q))
    {
        printf("Queue is empty");
        return;
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

int is_empty(Queue *q)
{
    if (q->front == q->rear)
        return 1;
    else
        return 0;
}

int is_full(Queue *q)
{
    if ((q->rear + 1) % MAX_QUEUE_SIZE == q->front)
        return 1;
    else
        return 0;
}
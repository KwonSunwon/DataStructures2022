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

void queue_init(Queue *);
void enqueue(Queue *, qData);
qData dequeue(Queue *);
int is_empty(Queue *);
int is_full(Queue *);

AVLNode *AVL_insert(AVLNode *, int);
AVLNode *AVL_remove(AVLNode *, int);

AVLNode *find_node(AVLNode *);

void level_order(AVLNode *);

int get_balance(AVLNode *);
int get_height(AVLNode *);

AVLNode *balance(AVLNode *);

AVLNode *rotate_right(AVLNode *);
AVLNode *rotate_left(AVLNode *);

AVLNode *LL_rotate(AVLNode *);
AVLNode *RR_rotate(AVLNode *);
AVLNode *LR_rotate(AVLNode *);
AVLNode *RL_rotate(AVLNode *);

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
    if (!root)
    {
        AVLNode *new = (AVLNode *)malloc(sizeof(AVLNode));
        new->key = key;
        new->left = NULL;
        new->right = NULL;
        root = new;
    }
    else if (root->key > key)
    {
        root->left = AVL_insert(root->left, key);
        root = balance(root);
    }
    else if (root->key < key)
    {
        root->right = AVL_insert(root->right, key);
        root = balance(root);
    }
    else if (root->key == key)
        printf("중복된 데이터\n");

    return root;
}

AVLNode *AVL_remove(AVLNode *root, int key)
{
    AVLNode *temp = NULL;

    if (!root)
        return root;

    if (root->key > key)
    {
        root->left = AVL_remove(root->left, key);
    }
    else if (root->key < key)
    {
        root->right = AVL_remove(root->right, key);
    }
    else
    {
        if ((root->left == NULL) || (root->right == NULL))
        {
            temp = root->left ? root->left : root->right;
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            free(temp);
        }
        else
        {
            temp = find_node(root->right);
            root->key = temp->key;
            root->right = AVL_remove(root->right, temp->key);
        }
    }

    if (root == NULL)
        return root;

    root = balance(root);
    return root;
}

AVLNode *find_node(AVLNode *node)
{
    AVLNode *pos = node;
    while (pos->left)
        pos = pos->left;
    return pos;
}

AVLNode *balance(AVLNode *root)
{
    int balanceFactor = get_balance(root);

    if (balanceFactor > 1)
    {
        if (get_balance(root->left) >= 0)
            root = LL_rotate(root);
        else
            root = LR_rotate(root);
    }
    else if (balanceFactor < -1)
    {
        if (get_balance(root->right) <= 0)
            root = RR_rotate(root);
        else
            root = RL_rotate(root);
    }

    return root;
}

AVLNode *rotate_left(AVLNode *root)
{
    AVLNode *child = root->right;
    if (child != NULL)
        root->right = child->left;
    else
        root->right = NULL;
    child->left = root;
    return child;
}
AVLNode *rotate_right(AVLNode *root)
{
    AVLNode *child = root->left;
    if (child != NULL)
        root->left = child->right;
    else
        root->left = NULL;
    child->right = root;
    return child;
}

AVLNode *LL_rotate(AVLNode *root)
{
    return rotate_right(root);
}
AVLNode *RR_rotate(AVLNode *root)
{
    return rotate_left(root);
}
AVLNode *LR_rotate(AVLNode *root)
{
    root->left = rotate_left(root->left);
    return rotate_right(root);
}
AVLNode *RL_rotate(AVLNode *root)
{
    root->right = rotate_right(root->right);
    return rotate_left(root);
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
    printf("\n");
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
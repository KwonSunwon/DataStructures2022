#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 1000

typedef struct _Element
{
    int id_num;
    char name[10];
} Element;

typedef struct _TreeNode
{
    Element std;
    struct _TreeNode *left, *right;
} TreeNode;

typedef struct _qData
{
    TreeNode *node;
    int level;
} qData;

typedef struct _Queue
{
    qData data[MAX_QUEUE_SIZE];
    int front;
    int rear;
    int count;
} Queue;

void queue_init(Queue *);
void enqueue(Queue *, qData);
qData dequeue(Queue *);
int is_empty(Queue *);

TreeNode *insert_node(TreeNode *, Element);
int get_node_count(TreeNode *);
int get_leaf_count(TreeNode *);
int get_height(TreeNode *);
void level_order(TreeNode *);
void inorder(TreeNode *);
int search(TreeNode *, int);
TreeNode *delete_node(TreeNode *, int);
TreeNode *find_node(TreeNode *);

int main()
{
    TreeNode *root = NULL;
    Element item;

    item.id_num = 2021006;
    strcpy(item.name, "name6");
    root = insert_node(root, item);
    item.id_num = 2021001;
    strcpy(item.name, "name1");
    root = insert_node(root, item);
    item.id_num = 2021009;
    strcpy(item.name, "name9");
    root = insert_node(root, item);
    item.id_num = 2021007;
    strcpy(item.name, "name7");
    root = insert_node(root, item);
    item.id_num = 2021003;
    strcpy(item.name, "name3");
    root = insert_node(root, item);
    item.id_num = 2021002;
    strcpy(item.name, "name2");
    root = insert_node(root, item);
    item.id_num = 2021005;
    strcpy(item.name, "name5");
    root = insert_node(root, item);
    item.id_num = 2021004;
    strcpy(item.name, "name4");
    root = insert_node(root, item);
    item.id_num = 2021008;
    strcpy(item.name, "name8");
    root = insert_node(root, item);
    item.id_num = 2021010;
    strcpy(item.name, "name10");
    root = insert_node(root, item);

    printf("이진 탐색 트리의 노드 수, leaf노드 수, 높이 구하기\n");
    printf("노드 수 = %d \nleaf 노드 수 = %d \n높이 = %d \n\n", get_node_count(root), get_leaf_count(root), get_height(root));

    printf("이진 탐색 트리 레벨 탐색 순회 결과\n");
    level_order(root);
    printf("\n\n");

    printf("이진 탐색 트리 중위 순회 결과 \n");
    inorder(root);

    printf("\n\n이진 탐색 트리에서 2021009 검색\n");
    if (search(root, 2021009) != NULL)
        printf("이진 탐색 트리에서 2021009을 발견함 \n");
    else
        printf("이진 탐색 트리에서 2021009을 발견못함 \n");

    printf("\n이진 탐색 트리에서 2021006 삭제\n");
    delete_node(root, 2021006);

    printf("\n\n이진 탐색 트리 중위 순회 결과 \n");
    inorder(root);
    printf("\n\n");

    return 0;
}

TreeNode *insert_node(TreeNode *root, Element item)
{
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    newNode->std = item;
    newNode->left = NULL;
    newNode->right = NULL;

    TreeNode *pos = root;

    if (!root)
        root = newNode;
    else
    {
        while (1)
        {
            if (pos->std.id_num > item.id_num)
            {
                if (!pos->left)
                {
                    pos->left = newNode;
                    break;
                }
                pos = pos->left;
            }
            else if (pos->std.id_num < item.id_num)
            {
                if (!pos->right)
                {
                    pos->right = newNode;
                    break;
                }
                pos = pos->right;
            }
            else if (pos->std.id_num == item.id_num)
            {
                free(newNode);
                break;
            }
        }
    }
    return root;
}

int get_node_count(TreeNode *root)
{
    int count = 0;
    if (root)
        count = 1 + get_node_count(root->left) + get_node_count(root->right);
    return count;
}

int get_leaf_count(TreeNode *root)
{
    int count = 0;
    if (root)
    {
        if (!root->left && !root->right)
            return 1;
        else
            count = get_leaf_count(root->left) + get_leaf_count(root->right);
    }
    return count;
}

int get_height(TreeNode *root)
{
    int height = 0;
    if (root)
        height = 1 + max(get_height(root->left), get_height(root->right));
    return height;
}

void level_order(TreeNode *root)
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
            printf("[%d] ", data.node->std.id_num);
            continue;
        }
        printf("[%d] ", data.node->std.id_num);
    }
}

void inorder(TreeNode *root)
{
    if (root)
    {
        inorder(root->left);
        printf("[%d] ", root->std.id_num);
        inorder(root->right);
    }
}

int search(TreeNode *root, int id)
{
    while (root)
    {
        if (root->std.id_num == id)
            return 1;

        if (root->std.id_num > id)
            root = root->left;
        else if (root->std.id_num < id)
            root = root->right;
    }
    return 0;
}

TreeNode *delete_node(TreeNode *root, int id)
{
    /*
    TreeNode *pos = root;
    TreeNode *delNode = NULL;
    TreeNode *pNode = NULL;

    if (root->std.id_num == id)
    {
        delNode = root;
        pos = delNode;

        while (!pos->left && !pos->right)
        {
            if (pos->left)
                pos = pos->left;
            else if (pos->right)
                pos = pos->right;
        }

        if (pos != delNode->left)
            pos->left = delNode->left;
        if (pos != delNode->right)
            pos->right = delNode->right;

        free(delNode);
        return;
    }
    else
    {
        while (pos)
        {
            if (pos->std.id_num == id)
                delNode = pos;

            if (pos->std.id_num > id)
            {
                pNode = pos;
                pos = pos->left;
            }
            else if (pos->std.id_num < id)
            {
                pNode = pos;
                pos = pos->right;
            }
        }
    }

    if (!delNode)
    {
        printf("삭제할 노드가 없습니다.\n");
        return;
    }

    if (!delNode->left && !delNode->right)
    {
        if (pNode->left == delNode)
            pNode->left = NULL;
        else if (pNode->right == delNode)
            pNode->right = NULL;
        free(delNode);
    }
    else if (!delNode->right)
    {
        if (pNode->left == delNode)
            pNode->left = delNode->left;
        else if (pNode->right == delNode)
            pNode->right = delNode->left;
        free(delNode);
    }
    else if (!delNode->left)
    {
        if (pNode->left == delNode)
            pNode->left = delNode->right;
        else if (pNode->right == delNode)
            pNode->right = delNode->right;
        free(delNode);
    }
    else
    {
        pos = delNode;
        while (!pos->left && !pos->right)
        {
            if (pos->left)
                pos = pos->left;
            else if (pos->right)
                pos = pos->right;
        }

        if (pos != delNode->left)
            pos->left = delNode->left;
        if (pos != delNode->right)
            pos->right = delNode->right;

        if (pNode->left == delNode)
            pNode->left = pos;
        else if (pNode->right == delNode)
            pNode->right = pos;

        free(delNode);
    }*/

    TreeNode *sub = NULL;

    if (!root)
        return root;

    if (root->std.id_num > id)
        root->left = delete_node(root->left, id);
    else if (root->std.id_num < id)
        root->right = delete_node(root->right, id);
    else
    {
        if (!root->left)
        {
            sub = root->right;
            free(root);
            return sub;
        }
        else if (!root->right)
        {
            sub = root->left;
            free(root);
            return sub;
        }

        sub = find_node(root->right);
        root->std = sub->std;
        root->right = delete_node(root->right, sub->std.id_num);
    }
    return root;
}

TreeNode *find_node(TreeNode *node)
{
    TreeNode *pos = node;
    while (pos->left)
        pos = pos->left;
    return pos;
}

void queue_init(Queue *q)
{
    q->front = -1;
    q->rear = -1;
    q->count = 0;
}

void enqueue(Queue *q, qData item)
{
    if (q->count == MAX_QUEUE_SIZE)
    {
        printf("Queue is full");
        return;
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
    q->count++;
}

qData dequeue(Queue *q)
{
    if (is_empty(q))
    {
        printf("Queue is empty");
        return;
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    q->count--;
    return q->data[q->front];
}

int is_empty(Queue *q)
{
    if (q->count == 0)
    {
        return 1;
    }
    else
        return 0;
}
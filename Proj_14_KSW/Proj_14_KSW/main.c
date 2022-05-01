#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define SIZE 100

typedef struct _TreeNode
{
    int data;
    struct _TreeNode *left, *right;
} TreeNode;

typedef struct _Stack
{
    TreeNode *data[SIZE];
    int top;
} Stack;

void inorder_rec(TreeNode *);
void preorder_rec(TreeNode *);
void postorder_rec(TreeNode *);

void inorder_iter(TreeNode *);
void preorder_iter(TreeNode *);
void postorder_iter(TreeNode *);

void init(Stack *);
void push(Stack *, TreeNode *);
TreeNode *pop(Stack *);

// Full Binary Tree node number 1~15(root : 1)
TreeNode n15 = {15, NULL, NULL};
TreeNode n14 = {14, NULL, NULL};
TreeNode n13 = {13, NULL, NULL};
TreeNode n12 = {12, NULL, NULL};
TreeNode n11 = {11, NULL, NULL};
TreeNode n10 = {10, NULL, NULL};
TreeNode n9 = {9, NULL, NULL};
TreeNode n8 = {8, NULL, NULL};
TreeNode n7 = {7, &n14, &n15};
TreeNode n6 = {6, &n12, &n13};
TreeNode n5 = {5, &n10, &n11};
TreeNode n4 = {4, &n8, &n9};
TreeNode n3 = {3, &n6, &n7};
TreeNode n2 = {2, &n4, &n5};
TreeNode n1 = {1, &n2, &n3};
TreeNode *root = &n1;

int main(void)
{
    printf("중위 순회(rec)=");
    inorder_rec(root);
    printf("\n");
    printf("중위 순회(itr)=");
    inorder_iter(root);
    printf("\n");
    printf("전위 순회(rec)=");
    preorder_rec(root);
    printf("\n");
    printf("전위 순회(itr)=");
    preorder_iter(root);
    printf("\n");
    printf("후위 순회(rec)=");
    postorder_rec(root);
    printf("\n");
    printf("후위 순회(itr)=");
    postorder_iter(root);
    printf("\n");
    return 0;
}

void inorder_rec(TreeNode *root)
{
    if (root)
    {
        inorder_rec(root->left);
        printf("[%d] ", root->data);
        inorder_rec(root->right);
    }
}
void preorder_rec(TreeNode *root)
{
    if (root)
    {
        printf("[%d] ", root->data);
        preorder_rec(root->left);
        preorder_rec(root->right);
    }
}
void postorder_rec(TreeNode *root)
{
    if (root)
    {
        postorder_rec(root->left);
        postorder_rec(root->right);
        printf("[%d] ", root->data);
    }
}

void inorder_iter(TreeNode *root)
{
    Stack s;
    init(&s);
    while (1)
    {
        for (; root; root = root->left)
            push(&s, root);
        root = pop(&s);
        if (!root)
            break;
        printf("[%d] ", root->data);
        root = root->right;
    }
}
void preorder_iter(TreeNode *root)
{
    Stack s;
    init(&s);
    while (1)
    {
        for (; root; root = root->left)
        {
            printf("[%d] ", root->data);
            push(&s, root);
        }
        root = pop(&s);
        if (!root)
            break;
        root = root->right;
    }
}
void postorder_iter(TreeNode *root) // 아마 스택 두 가지 사용
{
    Stack s1;
    Stack s2;
    init(&s1);
    init(&s2);

    push(&s1, root);

    while (1)
    {
        root = pop(&s1);
        if (!root)
            break;
        push(&s2, root);

        if (root->left)
            push(&s1, root->left);
        if (root->right)
            push(&s1, root->right);
    }

    while (1)
    {
        root = pop(&s2);
        if (!root)
            break;
        printf("[%d] ", root->data);
    }
}

void init(Stack *s)
{
    s->top = -1;
}
void push(Stack *s, TreeNode *p)
{
    if (s->top < SIZE - 1)
        s->data[++s->top] = p;
}
TreeNode *pop(Stack *s)
{
    TreeNode *p = NULL;
    if (s->top >= 0)
        p = s->data[s->top--];
    return p;
}

//		     15
//	     4        20
//    1	      16      25
// 중위 순회 = [1][4][15][16][20][25]
// 전위 순회 = [15][4][1][20][16][25]
// 후위 순회 = [1][4][16][25][20][15]

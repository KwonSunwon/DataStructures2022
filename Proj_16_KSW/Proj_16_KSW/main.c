// Prob 1. heap을 이용한 정렬 vs Selection 정렬 비교
// Prob 2. 하프만 코드 인코딩, 디코딩
#define PROB 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if PROB == 1

#define SIZE 100000

typedef int element;

typedef struct heap
{
    element data[SIZE + 1]; // 생성되는 데이터 개수는 SIZE 만큼인데 힙은 첫번째 인덱스(0)을 사용하지 않으므로
    int count;              // SIZE - 1 개 만큼이 됨. 때문에 +1 을 해줌.
} heap;

heap *create();
void init(heap *);
void insert(heap *, element);
element delete_heap(heap *);

void heap_sort(element *, element *, int);
void selection_sort(element *, element *, int);

int main(void)
{
    element *list, *sorted_list;
    int i, s_time, e_time;
    srand(15);
    list = (element *)malloc(sizeof(element) * SIZE);
    sorted_list = (element *)malloc(sizeof(element) * SIZE);
    for (i = 0; i < SIZE; i++)
        list[i] = rand();

    s_time = clock();
    heap_sort(list, sorted_list, SIZE);
    e_time = clock();
    printf("Heap Sort 걸린 시간 : %d msec\n", e_time - s_time);

    // for (int i = 0; i < SIZE; ++i)
    //     printf("%d ", sorted_list[i]);
    // printf("\n");

    s_time = clock();
    selection_sort(list, sorted_list, SIZE);
    e_time = clock();
    printf("Selection Sort 걸린 시간 : %d msec\n", e_time - s_time);

    // for (int i = 0; i < SIZE; ++i)
    //     printf("%d ", sorted_list[i]);
    // printf("\n");

    return 0;
}

heap *create()
{
    return (heap *)malloc(sizeof(heap));
}

void init(heap *heap)
{
    heap->count = 0;
}

void insert(heap *heap, element item)
{
    int idx;
    idx = ++heap->count;

    while ((idx != 1) && (item < heap->data[idx / 2]))
    {
        heap->data[idx] = heap->data[idx / 2];
        idx /= 2;
    }
    heap->data[idx] = item;
}

element delete_heap(heap *heap)
{
    int parent, child;
    element item, tmp;

    item = heap->data[1];
    tmp = heap->data[heap->count--];
    parent = 1;
    child = 2;
    while (child <= heap->count)
    {
        if (child < heap->count && heap->data[child] > heap->data[child + 1])
            ++child;
        if (tmp <= heap->data[child])
            break;
        heap->data[parent] = heap->data[child];
        parent = child;
        child *= 2;
    }
    heap->data[parent] = tmp;
    return item;
}

void heap_sort(element *list, element *sorted_list, int size)
{
    heap *h = create();
    init(h);
    for (int i = 0; i < size; ++i)
        insert(h, list[i]);

    for (int i = 0; i < size; ++i)
        sorted_list[i] = delete_heap(h);
}

void selection_sort(element *list, element *sorted_list, int size)
{
    int temp;
    for (int i = 0; i < size - 1; ++i)
    {
        for (int j = i + 1; j < size; ++j)
        {
            if (list[i] > list[j])
            {
                temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }
    for (int i = 0; i < size; ++i)
        sorted_list[i] = list[i];
}

#elif PROB == 2

#define MAX_ELEMENT 200

typedef struct TreeNode
{
    int weight;
    char ch;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef TreeNode *element;

typedef struct HeapType
{
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

TreeNode *make_huffman_tree(int *, char *, int);
void destroy_tree(TreeNode *);

void huffman_decode(TreeNode *, char *);

TreeNode *make_tree(TreeNode *, TreeNode *);
int is_leaf(TreeNode *);
void print_array(int *, int);
void print_code(TreeNode *, int *, int);

HeapType *create();
void init(HeapType *);
void insert(HeapType *, element);
element delete_heap(HeapType *);

int main()
{
    char ch_list[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'y', 'z'};
    int freq[] = {10, 6, 8, 12, 50, 7, 9, 10, 23, 2, 42, 3, 12, 22, 13, 14, 22, 42, 23, 11, 9, 10, 15, 1, 2};
    TreeNode *head;
    head = make_huffman_tree(freq, ch_list, 25);
    huffman_decode(head, "0100001010001001101010101001111001011100010111");
    destroy_tree(head);
}

TreeNode *make_huffman_tree(int *freq, char *ch_list, int n)
{
    HeapType *heap;
    element item, item1, item2;
    int code[100];
    int top = 0;

    heap = create();
    init(heap);

    for (int i = 0; i < n; ++i)
    {
        item = make_tree(NULL, NULL);
        item->ch = ch_list[i];
        item->weight = freq[i];
        insert(heap, item);
    }

    printf("허프만 코드를 위한 트리 생성\n");
    for (int i = 1; i < n; ++i)
    {
        item1 = delete_heap(heap);
        item2 = delete_heap(heap);
        item = make_tree(item1, item2);
        item->weight = item1->weight + item2->weight;
        printf("%d+%d->%d\n", item1->weight, item2->weight, item->weight);
        insert(heap, item);
    }

    printf("\n문자별 허프만 코드\n");
    item = delete_heap(heap);
    print_code(item, code, top);
    free(heap);
    return item;
}

void huffman_decode(TreeNode *decoder, char *code)
{
    printf("\n허프만 코드를 이용한 디코딩 : \nDecode ");
    int idx = 0;
    while (code[idx] != NULL)
        printf("%c", code[idx++]);
    printf("\n");

    TreeNode *pos = decoder;

    idx = 0;
    while (code[idx] != NULL)
    {
        if (code[idx] == '1') // left
        {
            printf("%c", '1');
            if (pos->left != NULL)
                pos = pos->left;
        }
        else if (code[idx] == '0') // right
        {
            printf("%c", '0');
            if (pos->right != NULL)
                pos = pos->right;
        }

        if (is_leaf(pos))
        {
            printf(" ==> %c\n", pos->ch);
            pos = decoder;
        }
        ++idx;
    }
}

void destroy_tree(TreeNode *root)
{
    if (root == NULL)
        return;
    destroy_tree(root->left);
    destroy_tree(root->right);
    free(root);
}

TreeNode *make_tree(TreeNode *left, TreeNode *right)
{
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->left = left;
    node->right = right;
    return node;
}

int is_leaf(TreeNode *root)
{
    return !(root->left) && !(root->right);
}

void print_array(int *code, int n)
{
    for (int i = 0; i < n; ++i)
        printf("%d", code[i]);
    printf("\n");
}

void print_code(TreeNode *root, int *code, int top)
{
    if (root->left)
    {
        code[top] = 1;
        print_code(root->left, code, top + 1);
    }
    if (root->right)
    {
        code[top] = 0;
        print_code(root->right, code, top + 1);
    }
    if (is_leaf(root))
    {
        printf("%c: ", root->ch);
        print_array(code, top);
    }
}

HeapType *create()
{
    return (HeapType *)malloc(sizeof(HeapType));
}

void init(HeapType *heap)
{
    heap->heap_size = 0;
}

void insert(HeapType *heap, element item)
{
    int idx;
    idx = ++heap->heap_size;

    while ((idx != 1) && (item->weight < heap->heap[idx / 2]->weight))
    {
        heap->heap[idx] = heap->heap[idx / 2];
        idx /= 2;
    }
    heap->heap[idx] = item;
}

element delete_heap(HeapType *heap)
{
    int parent, child;
    element item, tmp;

    item = heap->heap[1];
    tmp = heap->heap[heap->heap_size--];
    parent = 1;
    child = 2;
    while (child <= heap->heap_size)
    {
        if (child < heap->heap_size && heap->heap[child]->weight > heap->heap[child + 1]->weight)
            ++child;
        if (tmp->weight <= heap->heap[child]->weight)
            break;
        heap->heap[parent] = heap->heap[child];
        parent = child;
        child *= 2;
    }
    heap->heap[parent] = tmp;
    return item;
}

#endif
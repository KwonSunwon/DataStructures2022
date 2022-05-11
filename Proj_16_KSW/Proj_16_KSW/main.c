// Prob 1. heap�� �̿��� ���� vs Selection ���� ��
// Prob 2. ������ �ڵ� ���ڵ�, ���ڵ�
#define PROB 1

#include <stdio.h>
#include <stdlib.h>

#if PROB == 1

#define SIZE 100

typedef int element;

typedef struct heap
{
    element data[SIZE + 1]; // �����Ǵ� ������ ������ SIZE ��ŭ�ε� ���� ù��° �ε���(0)�� ������� �����Ƿ�
    int count;              // SIZE - 1 �� ��ŭ�� ��. ������ +1 �� ����.
} heap;

heap *create();
void init(heap *);
int is_empty(heap *);
int is_full(heap *);
void insert(heap *, element);
element delete (heap *);
element find(heap *);

void heap_sort(element *, element *, int);
void selection_sort(element *, element *, int);

int main(void)
{
    element *list, *sorted_list;
    int i, s_time, e_time;
    srand(100);
    list = (element *)malloc(sizeof(element) * SIZE);
    sorted_list = (element *)malloc(sizeof(element) * SIZE);
    for (i = 0; i < SIZE; i++)
        list[i] = rand();

    s_time = clock();
    heap_sort(list, sorted_list, SIZE);
    e_time = clock();
    printf("Heap Sort �ɸ� �ð� : %d msec\n", e_time - s_time);

    s_time = clock();
    selection_sort(list, sorted_list, SIZE);
    e_time = clock();
    printf("Selection Sort �ɸ� �ð� : %d msec\n", e_time - s_time);

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

int is_empty(heap *heap)
{
    if (heap->count == 0)
        return 1;
    else
        return 0;
}

int is_full(heap *heap)
{
    if (heap->count == SIZE + 1)
        return 1;
    else
        return 0;
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

element delete (heap *heap)
{
    
}

element find(heap *heap);

void heap_sort(element *list, element *sorted_list, int size)
{
}

void selection_sort(element *list, element *sorted_list, int size)
{
}

#elif PROB == 2

#endif
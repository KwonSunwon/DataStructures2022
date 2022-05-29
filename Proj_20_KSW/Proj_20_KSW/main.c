#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

#define SIZE 100000

typedef int element;

typedef struct heap
{
    element data[SIZE + 1];
    int count;
} heap;
heap *create();
void init(heap *);
void insert(heap *, element);
element delete_heap(heap *);

typedef struct Queue
{
    element data[SIZE];
    int front, rear;
} Queue;
void initQueue(Queue *);
int isFull(Queue *);
int isEmpty(Queue *);
void enqueue(Queue *, element);
element dequeue(Queue *);

void selection_sort(int *, int);
void insertion_sort(int *, int);
void bubble_sort(int *, int);

void inc_insertion_sort(int *, int, int, int);
void shell_sort(int *, int);

void merge(int *, int, int, int);
void merge_sort(int *, int, int);

int partition(int *, int, int);
void quick_sort(int *, int, int);

void heap_sort(int *, int);

void radix_sort(int *, int);

int main()
{
    int i, s_time, e_time;
    int *list = (int *)malloc(sizeof(int) * SIZE);
    int *data = (int *)malloc(sizeof(int) * SIZE);
    int *sorted = (int *)malloc(sizeof(int) * SIZE);
    printf("Data Å©±â : %d \n", SIZE);
    srand(100);
    for (i = 0; i < SIZE; i++)
        data[i] = rand();

    memcpy(list, data, sizeof(int) * SIZE);
    s_time = clock();
    selection_sort(list, SIZE);
    e_time = clock();
    printf("¼±ÅÃÁ¤·Ä ½Ã°£ : %d\n", e_time - s_time);
    // if (SIZE <= 100)
    // {
    //     for (i = 0; i < SIZE; i++)
    //         printf("%d ", list[i]);
    //     printf("\n");
    // }

    memcpy(list, data, sizeof(int) * SIZE);
    s_time = clock();
    insertion_sort(list, SIZE);
    e_time = clock();
    printf("»ðÀÔÁ¤·Ä ½Ã°£ : %d\n", e_time - s_time);
    // if (SIZE <= 100)
    // {
    //     for (i = 0; i < SIZE; i++)
    //         printf("%d ", list[i]);
    //     printf("\n");
    // }

    memcpy(list, data, sizeof(int) * SIZE);
    s_time = clock();
    bubble_sort(list, SIZE);
    e_time = clock();
    printf("¹öºíÁ¤·Ä ½Ã°£ : %d\n", e_time - s_time);
    // if (SIZE <= 100)
    // {
    //     for (i = 0; i < SIZE; i++)
    //         printf("%d ", list[i]);
    //     printf("\n");
    // }

    memcpy(list, data, sizeof(int) * SIZE);
    s_time = clock();
    shell_sort(list, SIZE);
    e_time = clock();
    printf("¼¿Á¤·Ä ½Ã°£ : %d\n", e_time - s_time);
    // if (SIZE <= 100)
    // {
    //     for (i = 0; i < SIZE; i++)
    //         printf("%d ", list[i]);
    //     printf("\n");
    // }

    memcpy(list, data, sizeof(int) * SIZE);
    s_time = clock();
    merge_sort(list, 0, SIZE - 1);
    e_time = clock();
    printf("º´ÇÕÁ¤·Ä ½Ã°£ : %d\n", e_time - s_time);
    // if (SIZE <= 100)
    // {
    //     for (i = 0; i < SIZE; i++)
    //         printf("%d ", list[i]);
    //     printf("\n");
    // }

    memcpy(list, data, sizeof(int) * SIZE);
    s_time = clock();
    quick_sort(list, 0, SIZE - 1);
    e_time = clock();
    printf("ÄüÁ¤·Ä ½Ã°£ : %d\n", e_time - s_time);
    // if (SIZE <= 100)
    // {
    //     for (i = 0; i < SIZE; i++)
    //         printf("%d ", list[i]);
    //     printf("\n");
    // }

    memcpy(list, data, sizeof(int) * SIZE);
    s_time = clock();
    heap_sort(list, SIZE);
    e_time = clock();
    printf("ÈüÁ¤·Ä ½Ã°£ : %d\n", e_time - s_time);
    // if (SIZE <= 100)
    // {
    //     for (i = 0; i < SIZE; i++)
    //         printf("%d ", list[i]);
    //     printf("\n");
    // }

    memcpy(list, data, sizeof(int) * SIZE);
    s_time = clock();
    radix_sort(list, SIZE); // ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿?? È£ï¿½ï¿½
    e_time = clock();
    printf("±â¼öÁ¤·Ä ½Ã°£ : %d\n", e_time - s_time);
    // if (SIZE <= 100)
    // {
    //     for (i = 0; i < SIZE; i++)
    //         printf("%d ", list[i]);
    //     printf("\n");
    // }

    free(data);
    free(list);
    free(sorted);
}

void selection_sort(int *list, int size)
{
    int i, j, least, temp;
    for (i = 0; i < size - 1; ++i)
    {
        least = i;
        for (j = i + 1; j < size; ++j)
            if (list[j] < list[least])
                least = j;
        SWAP(list[i], list[least], temp);
    }
}
void insertion_sort(int *list, int size)
{
    int key, j;
    for (int i = 1; i < size; ++i)
    {
        key = list[i];
        for (j = i - 1; j >= 0 && list[j] > key; --j)
            list[j + 1] = list[j];
        list[j + 1] = key;
    }
}
void bubble_sort(int *list, int size)
{
    int temp;
    for (int i = size - 1; i > 0; --i)
        for (int j = 0; j < i; ++j)
            if (list[j] > list[j + 1])
                SWAP(list[j], list[j + 1], temp);
}

void inc_insertion_sort(int *list, int first, int last, int gap)
{
    int i, j, key;
    for (i = first + gap; i <= last; i = i + gap)
    {
        key = list[i];
        for (j = i - gap; j >= first && key < list[j]; j = j - gap)
            list[j + gap] = list[j];
        list[j + gap] = key;
    }
}

void shell_sort(int *list, int size)
{
    int gap;
    for (gap = size / 2; gap > 0; gap = gap / 2)
    {
        if ((gap % 2) == 0)
            ++gap;
        for (int i = 0; i < gap; ++i)
            inc_insertion_sort(list, i, size - 1, gap);
    }
}

int sorted[SIZE];

void merge(int *list, int left, int mid, int right)
{
    int i, j, k, l;
    i = left;
    j = mid + 1;
    k = left;
    while (i <= mid && j <= right)
    {
        if (list[i] <= list[j])
            sorted[k++] = list[i++];
        else
            sorted[k++] = list[j++];
    }
    if (i > mid)
        for (l = j; l <= right; l++)
            sorted[k++] = list[l];
    else
        for (l = i; l <= mid; l++)
            sorted[k++] = list[l];
    for (l = left; l <= right; l++)
        list[l] = sorted[l];
}
void merge_sort(int *list, int left, int right)
{
    int mid;
    if (left < right)
    {
        mid = (left + right) / 2;
        merge_sort(list, left, mid);
        merge_sort(list, mid + 1, right);
        merge(list, left, mid, right);
    }
}

int partition(int *list, int left, int right)
{
    int pivot, temp;
    int low, high;

    low = left;
    high = right + 1;
    pivot = list[left];
    do
    {
        do
            low++;
        while (low <= right && list[low] < pivot);
        do
            high--;
        while (high >= left && list[high] > pivot);
        if (low < high)
            SWAP(list[low], list[high], temp);
    } while (low < high);

    SWAP(list[left], list[high], temp);
    return high;
}
void quick_sort(int *list, int left, int right)
{
    if (left < right)
    {
        int q = partition(list, left, right);
        quick_sort(list, left, q - 1);
        quick_sort(list, q + 1, right);
    }
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
void heap_sort(int *list, int size)
{
    heap *h = create();
    init(h);
    for (int i = 0; i < size; ++i)
        insert(h, list[i]);

    for (int i = 0; i < size; ++i)
        list[i] = delete_heap(h);
}

#define BUCKET 10
#define DIGITS 5

void radix_sort(int *list, int size)
{
    int i, b, d, factor = 1;
    Queue q[BUCKET];

    for (b = 0; b < BUCKET; ++b)
        initQueue(&q[b]);

    for (d = 0; d < DIGITS; ++d)
    {
        for (i = 0; i < size; ++i)
            enqueue(&q[(list[i] / factor) % 10], list[i]);

        for (b = i = 0; b < BUCKET; ++b)
            while (!isEmpty(&q[b]))
                list[i++] = dequeue(&q[b]);
        factor *= 10;
    }
}

void initQueue(Queue *q)
{
    q->front = 0;
    q->rear = 0;
}

int isFull(Queue *q)
{
    if ((q->rear + 1) % SIZE == q->front)
        return 1;
    else
        return 0;
}

int isEmpty(Queue *q)
{
    if (q->front == q->rear)
        return 1;
    else
        return 0;
}

void enqueue(Queue *q, element e)
{
    if (isFull(q))
        printf("Queue is full\n");
    else
    {
        q->rear = (q->rear + 1) % SIZE;
        q->data[q->rear] = e;
    }
}

element dequeue(Queue *q)
{
    if (isEmpty(q))
        printf("Queue is empty\n");
    else
    {
        q->front = (q->front + 1) % SIZE;
        return q->data[q->front];
    }
}
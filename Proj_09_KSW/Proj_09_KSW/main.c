#include <stdio.h>
#include <stdlib.h>

#define MAX_LIST_SIZE 100
typedef int ELEMENT;

#define PROB 1

// TODO Array Definition
#if PROB == 1
typedef struct _ARRAYLIST
{
    ELEMENT data[MAX_LIST_SIZE];
    int count;
} LIST;

void init(LIST *);
int add(LIST *, ELEMENT);
int delete (LIST *, ELEMENT);
void clear(LIST *);
int is_in_list(LIST *, ELEMENT);
int get_length(LIST *);
int is_empty(LIST *);
int is_full(LIST *);
void display(LIST *);
int get_entry(LIST *, int);

// TODO LinkedList Definition
#elif PROB == 2

typedef struct _LINKEDLIST
{
    ELEMENT data;
    struct _LINKEDLIST *next;
    int count;
} LIST;

void init(LIST *);
int add(LIST *, ELEMENT);
int delete (LIST *, ELEMENT);
void clear(LIST *);
int is_in_list(LIST *, ELEMENT);
int get_length(LIST *);
int is_empty(LIST *);
int is_full(LIST *);
void display(LIST *);
int get_entry(LIST *, int);

#endif

int main()
{
    LIST list;
    char ch;

    init(&list);

    srand(100);
    while (1)
    {
        ELEMENT item = rand();
        add(&list, item);
        display(&list);
        ch = getch();
        if (ch == 'q')
            break;
    }
    printf("get_length : %d \n", get_length(&list));
    printf("is_empty : %d, is_full : %d \n", is_empty(&list), is_full(&list));
    printf("get_entry : %d위치의 데이터는 %d\n", 5, get_entry(&list, 5));
    printf("is_in_list : %d의 위치는 %d \n", 5415, is_in_list(&list, 5415));
    printf("is_in_list : %d의 위치는 %d \n", 10, is_in_list(&list, 10));
    printf("delete : %d의 위치는 %d \n", 5415, delete (&list, 5415));
    display(&list);
    printf("call clear\n");
    clear(&list);
    display(&list);
    printf("리스트 길이 %d \n", get_length(&list));

    return 0;
}

// TODO Array Declaration
#if PROB == 1
void init(LIST *list)
{
    list->count = 0;
}
int add(LIST *list, ELEMENT element)
{
    if (list->count == 0)
    {
        list->data[0] = element;
        ++list->count;
        return 1;
    }
    else if (is_full(list))
        return 0;
    else
    {
        int idx = 0;
        while (idx != list->count)
        {
            if (list->data[idx] >= element)
                break;
            ++idx;
        }

        if (idx == list->count)
        {
            list->data[idx] = element;
            ++list->count;
        }
        else
        {
            for (int i = list->count; i > idx - 1; --i)
                list->data[i + 1] = list->data[i];
            list->data[idx] = element;
            ++list->count;
        }
        return 1;
    }
}
int delete (LIST *list, ELEMENT element)
{
    if (is_empty(list))
        return -1;
    int idx = 0;
    while (idx != list->count)
    {
        if (list->data[idx] == element)
        {
            for (int i = idx; i < list->count - 1; ++i)
            {
                list->data[i] = list->data[i + 1];
            }
            --list->count;
            return idx;
        }
        ++idx;
    }
    return -1;
}
void clear(LIST *list)
{
    list->count = 0;
}
int is_in_list(LIST *list, ELEMENT element)
{
    int idx = 0;
    while (idx != list->count)
    {
        if (list->data[idx] == element)
            return idx;
        ++idx;
    }
    return -1;
}
int get_length(LIST *list)
{
    return list->count;
}
int is_empty(LIST *list)
{
    if (list->count == 0)
        return 1;
    else
        return 0;
}
int is_full(LIST *list)
{
    if (list->count == MAX_LIST_SIZE)
        return 1;
    else
        return 0;
}
void display(LIST *list)
{
    int idx = 0;
    while (idx != list->count)
    {
        printf("%d->", list->data[idx++]);
    }
    printf("\n");
}
int get_entry(LIST *list, int idx)
{
    if (list->count < idx)
        return -1;
    else
        return list->data[idx];
}

// TODO LinkedList Declaration
#elif PROB == 2

void init(LIST *list)
{
    list->data = -1;
    list->next = NULL;
    list->count = 0;
}
int add(LIST *list, ELEMENT element)
{
    LIST *newNode = (LIST *)malloc(sizeof(LIST));
    newNode->data = element;
    newNode->next = NULL;
    newNode->count = -1;

    if (list->count == 0)
    {
        list->next = newNode;
        ++list->count;
        return 1;
    }
    else if (is_full(list))
        return 0;
    else
    {
        LIST *pos = list->next;
        while (pos->next != NULL)
        {
            if (pos->next->data >= element)
            {
                newNode->next = pos->next;
                pos->next = newNode;
                ++list->count;
                return 1;
            }
            pos = pos->next;
        }
        pos->next = newNode;
        ++list->count;
        return 1;
    }

    ++list->count;
}
int delete (LIST *list, ELEMENT element)
{
    LIST *pos = list->next;
    LIST *prev = pos;
    int idx = 0;

    if (is_empty(list))
    {
        return -1;
    }

    if (list->count == 1)
    {
        free(pos);
        return 0;
    }

    while (pos->next != NULL)
    {
        if (pos->data == element)
        {
            prev->next = pos->next;
            free(pos);
            --list->count;
            return idx;
        }
        ++idx;
        prev = pos;
        pos = pos->next;
    }
    return -1;
}
void clear(LIST *list)
{
    if (is_empty(list))
        return;
    else
    {
        while (list->next != NULL)
        {
            LIST *del = list->next;
            list->next = del->next;
            free(del);
        }
    }
    list->count = 0;
}
int is_in_list(LIST *list, ELEMENT element)
{
    LIST *pos = list->next;
    int idx = 0;
    while (pos->next != NULL)
    {
        if (pos->data == element)
        {
            return idx;
        }
        ++idx;
        pos = pos->next;
    }
    return -1;
}
int get_length(LIST *list)
{
    return list->count;
}
int is_empty(LIST *list)
{
    if (list->count == 0)
        return 1;
    else
        return 0;
}
int is_full(LIST *list)
{
    if (list->count == MAX_LIST_SIZE)
        return 1;
    else
        return 0;
}
void display(LIST *list)
{
    if (is_empty(list))
    {
        printf("\n");
        return;
    }

    if (list->count == 1)
    {
        printf("%d->", list->next->data);
        printf("\n");
        return;
    }
    LIST *pos = list->next;
    while (pos->next != NULL)
    {
        printf("%d->", pos->data);
        pos = pos->next;
    }
    printf("%d->", pos->data);
    printf("\n");
}
int get_entry(LIST *list, int idx)
{
    if (list->count < idx)
        return -1;
    LIST *pos = list->next;
    for (int i = 0; i < idx; ++i)
        pos = pos->next;
    return pos->data;
}

#endif
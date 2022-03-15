#define _CRT_SECURE_NO_WARNINGS

#include <time.h>
#include "linkedlist.h"
#include "dlinkedlist.h"

int WhoIsPrecede(int d1, int d2) {
    if (d1 < d2)
        return 0;
    else
        return 1;
}


int main()
{
    int dataSize;
    int seed;

    printf("Data Size : ");
    scanf("%d", &dataSize);
    printf("Seed : ");
    scanf("%d", &seed);

    srand(seed);
    time_t start = time(NULL);
    
    //List list;
    //ListInit(&list);

    node* head = NULL;

    //SetSortRule(&list, WhoIsPrecede);
    
    printf("1\n");
    for (int i = 0; i < dataSize; ++i)
    {
        addNode(&head, rand());
        //LInsert(&list , rand());
    }
    printf("2\n");

    time_t end = time(NULL);

    printf("Linked List time cost : %ld\n", end - start);
    //printNode(head);

    int *arr = malloc(sizeof(int) * dataSize);

    start = time(NULL);

    int temp = 0;
    int num = 0;

    srand(seed);

    printf("3\n");
    for (int i = 0; i < dataSize; ++i)
    {
        arr[i] = rand();
    }
    printf("4\n");
    for (int i = 0; i < dataSize - 1; ++i)
        for (int j = 0; j < dataSize - 1 - i; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    printf("5\n");
    end = time(NULL);

    printf("Array time cost : %ld\n", end - start);
    //for (int i = 0; i < dataSize; ++i)
    //    printf("%d\t", arr[i]);

    free(arr);

    return;
}
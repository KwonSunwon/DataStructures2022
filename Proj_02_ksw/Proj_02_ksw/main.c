#define _CRT_SECURE_NO_WARNINGS

#include <time.h>
#include "linkedlist.h"

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

    node *head = NULL;

    for (int i = 0; i < dataSize; ++i)
    {
        addNode(&head, rand());
    }

    time_t end = time(NULL);

    printf("Linked List time cost : %ld\n", end - start);
    // printNode(head);

    int *arr = malloc(sizeof(int) * dataSize);

    start = time(NULL);

    int num = 0;

    srand(seed);

    arr[0] = rand();
    for (int i = 1; i < dataSize; ++i)
    {
        num = rand();
        for (int j = 0; j < i; ++j)
        {
            if (arr[j] > num)
            {
                memcpy(arr + j + 1, arr + j, sizeof(int) * (i - j));
                arr[j] = num;
                break;
            }
            else if (j == i - 1)
            {
                arr[i] = num;
                break;
            }
        }
    }

    end = time(NULL);

    printf("Array time cost : %ld\n", end - start);
    //for (int i = 0; i < dataSize; ++i)
    //    printf("%d\t", arr[i]);

    free(arr);

    return;
}
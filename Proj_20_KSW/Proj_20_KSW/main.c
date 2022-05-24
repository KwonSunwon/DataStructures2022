#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SIZE 100

void selection_sort(int *, int);
void insertion_sort(int *, int);
void bubble_sort(int *, int);
void shell_sort(int *, int);
void merge_sort(int *, int);
void quick_sort(int *, int);
void heap_sort(int *, int);
void radix_sort(int *, int);

int main()
{
    int i, s_time, e_time;
    int *list = (int *)malloc(sizeof(int) * SIZE);
    int *data = (int *)malloc(sizeof(int) * SIZE);
    int *sorted = (int *)malloc(sizeof(int) * SIZE);
    printf("Data 크기 : %d \n", SIZE);
    srand(100);
    for (i = 0; i < SIZE; i++) // 난수 생성 및 출력
        data[i] = rand();      // 난수 발생

    memcpy(list, data, sizeof(int) * SIZE);
    s_time = clock();
    selection_sort(list, SIZE); // 선택정렬 호출
    e_time = clock();
    printf("선택정렬 시간 : %d\n", e_time - s_time);
    if (SIZE <= 100)
    {
        for (i = 0; i < SIZE; i++)
            printf("%d ", list[i]);
        printf("\n");
    }

    memcpy(list, data, sizeof(int) * SIZE);
    s_time = clock();
    insertion_sort(list, SIZE);
    e_time = clock();
    printf("삽입정렬 시간 : %d\n", e_time - s_time);
    if (SIZE <= 100)
    {
        for (i = 0; i < SIZE; i++)
            printf("%d ", list[i]);
        printf("\n");
    }

    memcpy(list, data, sizeof(int) * SIZE);
    s_time = clock();
    bubble_sort(list, SIZE);
    e_time = clock();
    printf("버블정렬 시간 : %d\n", e_time - s_time);
    if (SIZE <= 100)
    {
        for (i = 0; i < SIZE; i++)
            printf("%d ", list[i]);
        printf("\n");
    }

    memcpy(list, data, sizeof(int) * SIZE);
    s_time = clock();
    shell_sort(list, SIZE);
    e_time = clock();
    printf("셸정렬 시간 : %d\n", e_time - s_time);
    if (SIZE <= 100)
    {
        for (i = 0; i < SIZE; i++)
            printf("%d ", list[i]);
        printf("\n");
    }

    memcpy(list, data, sizeof(int) * SIZE);
    s_time = clock();
    merge_sort(list, 0, SIZE - 1);
    e_time = clock();
    printf("병합정렬 시간 : %d\n", e_time - s_time);
    if (SIZE <= 100)
    {
        for (i = 0; i < SIZE; i++)
            printf("%d ", list[i]);
        printf("\n");
    }

    memcpy(list, data, sizeof(int) * SIZE);
    s_time = clock();
    quick_sort(list, 0, SIZE - 1);
    e_time = clock();
    printf("퀵정렬 시간 : %d\n", e_time - s_time);
    if (SIZE <= 100)
    {
        for (i = 0; i < SIZE; i++)
            printf("%d ", list[i]);
        printf("\n");
    }

    memcpy(list, data, sizeof(int) * SIZE);
    s_time = clock();
    heap_sort(list, SIZE);
    e_time = clock();
    printf("힙정렬 시간 : %d\n", e_time - s_time);
    if (SIZE <= 100)
    {
        for (i = 0; i < SIZE; i++)
            printf("%d ", list[i]);
        printf("\n");
    }

    memcpy(list, data, sizeof(int) * SIZE);
    s_time = clock();
    radix_sort(list, SIZE); // 기수정렬 호출
    e_time = clock();
    printf("기수정렬 시간 : %d\n", e_time - s_time);
    if (SIZE <= 100)
    {
        for (i = 0; i < SIZE; i++)
            printf("%d ", list[i]);
        printf("\n");
    }

    free(data);
    free(list);
    free(sorted);
}

void selection_sort(int *, int);
void insertion_sort(int *, int);
void bubble_sort(int *, int);
void shell_sort(int *, int);
void merge_sort(int *, int);
void quick_sort(int *, int);
void heap_sort(int *, int);
void radix_sort(int *, int);
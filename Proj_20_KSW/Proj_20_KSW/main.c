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
    printf("Data ũ�� : %d \n", SIZE);
    srand(100);
    for (i = 0; i < SIZE; i++) // ���� ���� �� ���
        data[i] = rand();      // ���� �߻�

    memcpy(list, data, sizeof(int) * SIZE);
    s_time = clock();
    selection_sort(list, SIZE); // �������� ȣ��
    e_time = clock();
    printf("�������� �ð� : %d\n", e_time - s_time);
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
    printf("�������� �ð� : %d\n", e_time - s_time);
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
    printf("�������� �ð� : %d\n", e_time - s_time);
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
    printf("������ �ð� : %d\n", e_time - s_time);
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
    printf("�������� �ð� : %d\n", e_time - s_time);
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
    printf("������ �ð� : %d\n", e_time - s_time);
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
    printf("������ �ð� : %d\n", e_time - s_time);
    if (SIZE <= 100)
    {
        for (i = 0; i < SIZE; i++)
            printf("%d ", list[i]);
        printf("\n");
    }

    memcpy(list, data, sizeof(int) * SIZE);
    s_time = clock();
    radix_sort(list, SIZE); // ������� ȣ��
    e_time = clock();
    printf("������� �ð� : %d\n", e_time - s_time);
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
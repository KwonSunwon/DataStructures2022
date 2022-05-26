#include <stdio.h>
#include <stdlib.h>

#define SIZE 100000000
#define DATA 554654

int seqsearch(int[], int, int, int, int *);
int binsearch(int[], int, int, int, int *);
int search_interpolation(int[], int, int, int, int *);

int main(void)
{
    int i, s_time, e_time, count, result;
    int *list = (int *)malloc(sizeof(int) * SIZE);
    list[0] = 0;
    for (i = 1; i < SIZE; i++)
        list[i] = list[i - 1] + (rand() % 3);
    printf("Data ũ�� : %d, �˻� ������ : %d \n", SIZE, DATA);
    printf("----------------------------------------------\n");
    s_time = clock();
    result = seqsearch(list, 0, SIZE - 1, DATA, &count); // ����Ž�� ȣ��
    e_time = clock();
    if (result == -1)
        printf("�˻� ��� : �˻� ������ ���� \n");
    else
        printf("�˻���� : %d ��ġ���� ã�� \n", result);
    printf("����Ž�� �ҿ�ð� %d, ��Ƚ�� : %d\n\n", e_time - s_time, count);
    s_time = clock();
    result = binsearch(list, 0, SIZE - 1, DATA, &count); // ����Ž�� ȣ��
    e_time = clock();
    if (result == -1)
        printf("�˻� ��� : �˻� ������ ���� \n");
    else
        printf("�˻���� : %d ��ġ���� ã�� \n", result);
    printf("����Ž�� �ҿ�ð� %d, ��Ƚ�� : %d\n\n", e_time - s_time, count);
    s_time = clock();
    result = search_interpolation(list, 0, SIZE - 1, DATA, &count); //����Ž�� ȣ��
    e_time = clock();
    if (result == -1)
        printf("�˻� ��� : �˻� ������ ���� \n");
    else
        printf("�˻���� : %d ��ġ���� ã�� \n", result);
    printf("����Ž�� �ҿ�ð� %d, ��Ƚ�� : %d\n\n", e_time - s_time, count);
    free(list);
    return 0;
}

int seqsearch(int list[], int low, int high, int key, int *cnt)
{
    *cnt = 0;
    for (int i = low; i <= high; ++i)
    {
        ++*cnt;
        if (list[i] == key)
            return i;
    }
    return -1;
}

int binsearch(int list[], int low, int high, int key, int *cnt)
{
    *cnt = 0;
    int mid;
    while (low <= high)
    {
        ++*cnt;
        mid = (low + high) / 2;
        if (key == list[mid])
            return mid;
        else if (key > list[mid])
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

int search_interpolation(int list[], int low, int high, int key, int *cnt)
{
    *cnt = 0;
    int j;
    while ((list[high] >= key) && (key > list[low]))
    {
        ++*cnt;
        j = ((float)(key - list[low]) / (list[high] - list[low]) * (high - low)) + low + 0.5;
        if (key > list[j])
            low = j + 1;
        else if (key < list[j])
            high = j - 1;
        else
            low = j;
    }
    if (list[low] == key)
        return low;
    else
        return -1;
}
// Prob 1 반복적인 방법에선 2차원 배열
// Prob 2 재귀적이면 문제 해결에 상당히 오래걸림, 반복적인 방법을 잘 찾아야함
// Prob 4 이진탐색, 재귀적인 방법과 반복적인 방법
// 전부다 재귀적인 방법과 반복적인 방법(for) 두 방법을 전부 구현해야함.

#define PROB 2

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#if PROB == 1
int recBinomialCoef(int n, int k);
int itrBinomialCoef(int n, int k);

int main(void)
{
    int n, k;
    int result;
    time_t start, end;
    printf("Enter 'n', 'k' : ");
    scanf("%d %d", &n, &k);

    start = time(NULL);
    result = recBinomialCoef(n, k);
    end = time(NULL);
    printf("Recursion - Result : %d, Time : %ld\n", result, end - start);

    start = time(NULL);
    result = itrBinomialCoef(n, k);
    end = time(NULL);
    printf("Iteration - Result : %d, Time : %ld\n", result, end - start);
}

int recBinomialCoef(int n, int k)
{
    if (k == 0 || k == n)
        return 1;
    else
        return recBinomialCoef(n - 1, k - 1) + recBinomialCoef(n - 1, k);
}
int itrBinomialCoef(int n, int k)
{
    int i, j;
    int c[100][100];
    for (i = 1; i <= n; ++i)
        for (j = 0; j <= i; ++j)
        {
            if (j == 0 || j == i)
                c[i][j] = 1;
            else
                c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
        }
    return c[n][k];
}

#elif PROB == 2
int recAckerman(int m, int n);
int itrAckerman(int m, int n);

int main(void)
{
    int m, n;
    int result;
    time_t start, end;
    printf("Enter 'm', 'n' : ");
    scanf("%d %d", &m, &n);

    start = time(NULL);
    result = recAckerman(m, n);
    end = time(NULL);
    printf("Recursion - Result : %d, Time : %ld\n", result, end - start);

    start = time(NULL);
    result = itrAckerman(m, n);
    end = time(NULL);
    printf("Iteration - Result : %d, Time : %ld\n", result, end - start);
}

int recAckerman(int m, int n)
{
    if (m == 0)
        return n + 1;
    else if (n == 0)
        return recAckerman(m - 1, 1);
    else
        return recAckerman(m - 1, recAckerman(m, n - 1));
}
// long long int 배열 사용
int itrAckerman(int m, int n)
{
    long long int arr[100'000];
    int cnt = 0;

    arr[cnt++] = m;
    arr[cnt] = n;

    while (1)
    {
        if (cnt == 0)
        {
            return arr[cnt];
        }
        else if (arr[cnt - 1] == 0)
        {
            arr[cnt - 1] = arr[cnt] + 1;
            --cnt;
        }
        else if (arr[cnt] == 0)
        {
            --arr[cnt - 1];
            arr[cnt] = 1;
        }
        else
        {
            arr[cnt + 1] = arr[cnt] - 1;
            arr[cnt] = arr[cnt - 1];
            --arr[cnt - 1];
            ++cnt;
        }
    }
}

#elif PROB == 3
int recFibonacci(int n);
int itrFibonacci(int n);

int main(void)
{
    int n, result;
    printf("Enter 'n' : ");
    scanf("%d", &n);

    time_t start, end;

    start = time(NULL);
    result = recFibonacci(n);
    end = time(NULL);
    printf("Recursion - Result : %d, Time : %ld\n", result, end - start);

    start = time(NULL);
    result = itrFibonacci(n);
    end = time(NULL);
    printf("Interation - Result : %d, Time : %ld\n", result, end - start);
}

int recFibonacci(int n)
{
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
    else
        return recFibonacci(n - 2) + recFibonacci(n - 1);
}

int itrFibonacci(int n)
{
    int n1 = 0;
    int n2 = 1;
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
    else
    {
        for (int i = 0; i < n / 2; ++i)
        {
            n1 += n2;
            n2 += n1;
        }
        if (n % 2 == 0)
            return n1;
        else
            return n2;
    }
}

#elif PROB == 4
#define SIZE 1'000'000'000

int recBinarySearch(int *data, int x, int beginIdx, int endIdx);
int itrBinarySearch(int *data, int x, int beginIdx, int endIdx);

int main(void)
{
    int* data = (int*)malloc(sizeof(int) * SIZE);

    time_t start, end;

    for (int idx = 0; idx < SIZE; ++idx)
        data[idx] = idx;

    int x, result;
    printf("Input x : ");
    scanf("%d", &x);

    start = time(NULL);
    result = recBinarySearch(data, x, 0, SIZE);
    end = time(NULL);
    printf("idx : %d, time : %lf\n", result, end - start);

    start = time(NULL);
    result = itrBinarySearch(data, x, 0, SIZE);
    end = time(NULL);
    printf("idx : %d, time : %lf\n", result, end - start);

    free(data);
}

int recBinarySearch(int *data, int x, int beginIdx, int endIdx)
{
    int midIdx = (beginIdx + endIdx) / 2;

    if (data[midIdx] == x)
        return midIdx;
    else if (data[midIdx] > x)
        return recBinarySearch(data, x, beginIdx, midIdx);
    else if (data[midIdx] < x)
        return recBinarySearch(data, x, midIdx, endIdx);
}

int itrBinarySearch(int *data, int x, int beginIdx, int endIdx)
{
    int midIdx;
    while (beginIdx <= endIdx)
    {
        midIdx = (beginIdx + endIdx) / 2;
        if (data[midIdx] == x)
            return midIdx;
        else if (data[midIdx > x])
            endIdx = midIdx;
        else if (data[midIdx < x])
            beginIdx = midIdx;
    }
}

#endif
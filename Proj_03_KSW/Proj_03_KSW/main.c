// Prob 1 �ݺ����� ������� 2���� �迭
// Prob 2 ������̸� ���� �ذῡ ����� �����ɸ�, �ݺ����� ����� �� ã�ƾ���
// Prob 4 ����Ž��, ������� ����� �ݺ����� ���
// ���δ� ������� ����� �ݺ����� ���(for) �� ����� ���� �����ؾ���.

#define PROB 3

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#if PROB == 1
int recBinomialCoef(int n, int k);
int itrBinomialCoef(int n, int k);

int main(void)
{
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

int main(void)
{
}

int recAckerman(int m, int n)
{
    if (m == 0)
        return n - 1;
    else if (n == 0)
        return recAckerman(m - 1, 1);
    else
        return recAckerman(m - 1, recAckerman(m, n - 1));
}
// long long int �迭 ���

#elif PROB == 3
int recFibonacci(int n);
int itrFibonacci(int n);

int main(void)
{
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
}

#elif PROB == 4
#define SIZE 1000

int binarySearch(int data[], int x, int beginIdx, int endIdx);

int main(void)
{
    int data[SIZE];

    for (int idx = 0; idx < SIZE; ++idx)
        data[idx] = idx;

    int x;
    scanf("%d", &x);
    printf("idx : %d", binarySearch(data, x, 0, SIZE));
}

int binarySearch(int data[], int x, int beginIdx, int endIdx)
{
    int midIdx = endIdx / 2;

    if (data[midIdx] == x)
        return endIdx / 2;
    else if (data[midIdx] > x)
        return binarySearch(data, x, beginIdx, midIdx);
    else if (data[midIdx] < x)
        return binarySearch(data, x, midIdx, endIdx);
    // ó���� �� ���� �� ������ 2 �߰� ���� -1 �� +1
}

#endif
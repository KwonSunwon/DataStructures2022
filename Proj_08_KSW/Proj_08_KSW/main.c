#define PROB 3

#include "queue.h"
#include "stack.h"

#if PROB == 1
int main()
{
    QUEUE q;
    initQueue(&q);

    qELEMENT first = {1, 0};
    enqueue(&q, first);

    long check[MAX_QUEUE_SIZE] = {-1};
    int checkCnt = 0;

    int input;

    printf("���� ���̷��� �� �Է� : ");
    scanf("%d", &input);

    int already = 0;
    qELEMENT temp;
    qELEMENT in;
    while (1)
    {
        if (qisEmpty(q) == 1)
        {
            // printf("ť�� �����");
            break;
        }
        temp = dequeue(&q);

        if (temp.data == input)
            break;

        for (int i = 0; i < checkCnt; ++i)
            if (temp.data == check[i])
            {
                // printf("�̹� ó���� ��\n");
                already = 1;
                break;
            }

        if (already == 0)
        {
            check[checkCnt++] = temp.data;

            in.data = temp.data * 2;
            in.time = temp.time + 1;
            enqueue(&q, in);

            in.data = temp.data / 3;
            enqueue(&q, in);
        }
        if (isFull(q) || checkCnt == MAX_QUEUE_SIZE)
            break;
        already = 0;
    }
    if (!isFull(q) && !qisEmpty(q) && checkCnt != MAX_QUEUE_SIZE)
        printf("%d ������ �Ǵ� �� �ʿ��� �ҿ� �ð� : %d\n", input, temp.time);
    else
        printf("ť�� ��ȭ�����Դϴ�.\n");
}

// NOTE ������ ���ؿ��� Ǯ� ������ ����ѵ�? �������� �迭�ΰ� �Լ����µ�
// REF https://www.acmicpc.net/problem/1158
#elif PROB == 2

int main()
{
    int n, k;
    do
    {
        printf("���ӿ� �����ϴ� ����� �� n�� �����ϴ� k �� �Է� : ");
        scanf("%d %d", &n, &k);
    } while (!(n >= 1) || !(k >= 1) || !(k <= n));

    QUEUE q;
    initQueue(&q);

    for (int i = 0; i < n; ++i)
    {
        qELEMENT temp = {i + 1, 0};
        enqueue(&q, temp);
        if (isFull(q))
        {
            printf("ť ũ�⺸�� n �� ���� ŭ\n");
            return 0;
        }
    }

    qELEMENT temp;

    printf("���õ� ����� ��ȣ : ");
    while (1)
    {
        for (int i = 0; i < k - 1; ++i)
        {
            enqueue(&q, dequeue(&q));
        }

        temp = dequeue(&q);

        printf("%d ", temp);

        if (qisEmpty(q))
            break;
    }

    printf("\n���� ��Ƴ��� ����� %d ��ġ�� ���� �� �����\n", temp.data);
}

// NOTE �Է¹��� ������ RQ�� ���ؼ� �´ٸ� LQ�� �̵�
// ���ÿ��� ���ؼ� �̵� �� �� �ƴ϶�� �������� �̵�
#elif PROB == 3

int main()
{
    QUEUE rq, lq;
    STACK ms;

    init(&ms);
    initQueue(&rq);
    initQueue(&lq);

    int n = 10;
    int testNumberSquence[MAX_QUEUE_SIZE] = {5,4,3,2,1,6,7,8,9,10};

    for (int i = 0; i < n; ++i)
    {
        qELEMENT temp = {i + 1, 0};
        enqueue(&rq, temp);
    }

    ELEMENT tempMs;
    qELEMENT tempRq;
    qELEMENT tempLq;
    int idx = 0;

    while (!qisEmpty(rq))
    {
        tempRq = dequeue(&rq);

        if (testNumberSquence[idx] == tempRq.data)
        {
            enqueue(&lq, tempRq);
            ++idx;
        }
        else if (testNumberSquence[idx] == peek(ms))
        {
            while (testNumberSquence[idx] == peek(ms))
            {
                tempMs = pop(&ms);
                tempLq.data = tempMs;
                enqueue(&lq, tempLq);
                ++idx;
            }
            push(&ms, tempRq.data);
        }
        else
        {
            push(&ms, tempRq.data);
        }

        if (idx == n)
            break;
    }

    while (!isEmpty(ms))
    {
        tempMs = pop(&ms);
        tempLq.data = tempMs;
        enqueue(&lq, tempLq);
    }

    printf("%d���� �׽�Ʈ ����\n", n);

    int check = 0;
    for (int i = 0; i < n; ++i)
    {
        if (qisEmpty(lq))
        {
            check = 1;
            break;
        }
        if (testNumberSquence[i] != dequeue(&lq).data)
            check = 1;
    }

    for (int i = 0; i < n; ++i)
        printf("%d ", testNumberSquence[i]);
    printf("\n");

    if (check)
        printf("�������� ���� : �Ұ���\n");
    else
        printf("�������� ���� : ����\n");
}

#endif

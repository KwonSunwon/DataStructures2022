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

    printf("현재 바이러스 수 입력 : ");
    scanf("%d", &input);

    int already = 0;
    qELEMENT temp;
    qELEMENT in;
    while (1)
    {
        if (qisEmpty(q) == 1)
        {
            // printf("큐가 비었음");
            break;
        }
        temp = dequeue(&q);

        if (temp.data == input)
            break;

        for (int i = 0; i < checkCnt; ++i)
            if (temp.data == check[i])
            {
                // printf("이미 처리한 값\n");
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
        printf("%d 마리가 되는 데 필요한 소요 시간 : %d\n", input, temp.time);
    else
        printf("큐가 포화상태입니다.\n");
}

// NOTE 옜날에 백준에서 풀어본 문제랑 비슷한듯? 무슨무슨 배열인가 함수였는데
// REF https://www.acmicpc.net/problem/1158
#elif PROB == 2

int main()
{
    int n, k;
    do
    {
        printf("게임에 참여하는 사람의 수 n과 선택하는 k 값 입력 : ");
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
            printf("큐 크기보다 n 의 값이 큼\n");
            return 0;
        }
    }

    qELEMENT temp;

    printf("선택된 사람의 번호 : ");
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

    printf("\n최종 살아남은 사람은 %d 위치에 줄을 선 사람임\n", temp.data);
}

// NOTE 입력받은 수열과 RQ을 비교해서 맞다면 LQ로 이동
// 스택에서 비교해서 이동 둘 다 아니라면 스택으로 이동
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

    printf("%d개의 테스트 수열\n", n);

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
        printf("생성가능 여부 : 불가능\n");
    else
        printf("생성가능 여부 : 가능\n");
}

#endif

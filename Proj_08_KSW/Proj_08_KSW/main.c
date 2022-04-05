#define PROB 1

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

#elif PROB == 2
// NOTE 옜날에 백준에서 풀어본 문제랑 비슷한듯? 무슨무슨 배열인가 함수였는데

#elif PROB == 3
// NOTE 입력받은 수열과 RQ을 비교해서 맞다면 LQ로 이동
// 스택에서 비교해서 이동 둘 다 아니라면 스택으로 이동

#endif

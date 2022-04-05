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

#elif PROB == 2
// NOTE ������ ���ؿ��� Ǯ� ������ ����ѵ�? �������� �迭�ΰ� �Լ����µ�

#elif PROB == 3
// NOTE �Է¹��� ������ RQ�� ���ؼ� �´ٸ� LQ�� �̵�
// ���ÿ��� ���ؼ� �̵� �� �� �ƴ϶�� �������� �̵�

#endif

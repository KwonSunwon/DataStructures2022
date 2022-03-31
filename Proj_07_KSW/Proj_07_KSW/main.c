#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_QUEUE_SIZE 10
#define WORK_TIME 10'000

// front % MAX_QUEUE_SIZE == (rear + 1) % MAX_QUEUE_SIZE

typedef struct _ELEMENT
{
    char menu;
    int orderTime;
} ELEMENT;

typedef struct _QUEUE
{
    ELEMENT data[MAX_QUEUE_SIZE + 1];
    int front;
    int rear;
} QUEUE;

typedef struct _SERVER
{
    int processingTime;
    int restTime;
} SERVER;

// queue data : 메뉴의 종류, 손님이 큐에 들어온 시간

void initQueue(QUEUE *);
int isFull(QUEUE);
int isEmpty(QUEUE);
void enqueue(QUEUE *, ELEMENT);
ELEMENT dequeue(QUEUE *);

int main()
{
    QUEUE orderQueue;
    initQueue(&orderQueue);

    SERVER server1 = {-1, 0};
    SERVER server2 = {-1, 0};

    int totalService[5] = {0};
    int cancledOrder = 0;
    int cumulativeTime = 0;
    float averageTime = 0;

    int workTime = 0;
    srand(time(NULL));

    while (workTime <= WORK_TIME)
    {
        if (workTime % 5 == 0)
        {
            ELEMENT newOrder = {rand() % 5, workTime};
            if (!isFull(orderQueue))
                enqueue(&orderQueue, newOrder);
            else
                ++cancledOrder;
        }

        if (!server1.processingTime)
        {
            ELEMENT newProcess = dequeue(&orderQueue);
            server1.processingTime = // 각 메뉴의 시간만큼
            // 여기까지
        }

        ++workTime;
        --server1.processingTime;
        --server2.processingTime;
    }

    printf("=========== Results ============\n");
    for (int i = 0; i < 5; i++)
    {
        printf("MENU %d %d개 서비스, 누적대기시간 %d, 평균서비스시간 %f\n", i, totalService[i], cumulativeTime, averageTime);
    }
    printf("취소된 주문 %d 개\n", cancledOrder);
    printf("================================\n");
}

void initQueue(QUEUE *q)
{
    q->front = 0;
    q->rear = 0;
}

int isFull(QUEUE q)
{
    if ((q.rear + 1) % MAX_QUEUE_SIZE == q.front)
        return 1;
    else
        return 0;
}

int isEmpty(QUEUE q)
{
    if (q.front == q.rear)
        return 1;
    else
        return 0;
}

void enqueue(QUEUE *q, ELEMENT e)
{
    if (isFull)
        printf("Queue is full\n");
    else
    {
        if (q->rear == MAX_QUEUE_SIZE + 1)
            q->rear = 0;
        else
            ++q->rear;
        q->data[q->rear] = e;
    }
}

ELEMENT dequeue(QUEUE *q)
{
    if (ifEmpty(q))
        printf("Queue is empty\n");
    else
    {
        if (q->front == MAX_QUEUE_SIZE + 1)
            q->front = 0;
        else
            ++q->front;
        return q->data[q->front];
    }
}
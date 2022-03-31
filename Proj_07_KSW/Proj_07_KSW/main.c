#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_QUEUE_SIZE 10
#define WORK_TIME 10000

// front % MAX_QUEUE_SIZE == (rear + 1) % MAX_QUEUE_SIZE

typedef struct _ELEMENT
{
    int menu;
    int orderTime;
} ELEMENT;

typedef struct _QUEUE
{
    ELEMENT data[MAX_QUEUE_SIZE];
    int front;
    int rear;
} QUEUE;

typedef struct _SERVER
{
    ELEMENT order;
    int processingTime;
    int restTime;
} SERVER;

// queue data : 메뉴의 종류, 손님이 큐에 들어온 시간

void initQueue(QUEUE *);
int isFull(QUEUE);
int isEmpty(QUEUE);
void enqueue(QUEUE *, ELEMENT);
ELEMENT dequeue(QUEUE *);

int menuRequired(int);

int main()
{
    QUEUE orderQueue;
    initQueue(&orderQueue);

    SERVER server1 = {{-1, 0}, -1, 0};
    SERVER server2 = {{-1, 0}, -1, 0};

    int totalService[5] = {0};
    int cumulativeTime[5] = {0};
    int cancledOrder = 0;
    float averageTime = 0;

    int workTime = 0;
    srand(time(NULL));

    while (workTime <= WORK_TIME)
    {
        if (workTime % 7 == 0)
        {
            if (!isFull(orderQueue))
            {
                ELEMENT newOrder = {rand() % 5, workTime};
                enqueue(&orderQueue, newOrder);
            }
            else
                ++cancledOrder;
        }

        if (server1.order.menu == -1)
        {
            if (!isEmpty(orderQueue))
            {
                server1.order = dequeue(&orderQueue);
                server1.processingTime = menuRequired(server1.order.menu);
            }
            else
                ++server1.restTime;
        }
        else if (server1.processingTime == 0)
        {
            ++totalService[server1.order.menu];
            cumulativeTime[server1.order.menu] += workTime - server1.order.orderTime;
            server1.order.menu = -1;
        }

        if (server2.order.menu == -1)
        {
            if (!isEmpty(orderQueue))
            {
                server2.order = dequeue(&orderQueue);
                server2.processingTime = menuRequired(server2.order.menu);
            }
            else
                ++server2.restTime;
        }
        else if (server2.processingTime == 0)
        {
            ++totalService[server2.order.menu];
            cumulativeTime[server2.order.menu] += workTime - server2.order.orderTime;
            server2.order.menu = -1;
        }

        ++workTime;
        if (server1.order.menu != -1)
            --server1.processingTime;
        if (server2.order.menu != -1)
            --server2.processingTime;
    }

    printf("=========== Results ============\n");
    printf("큐의 갯수 : %d\n", MAX_QUEUE_SIZE);
    for (int i = 0; i < 5; i++)
    {
        averageTime = (float)cumulativeTime[i] / totalService[i];
        printf("MENU %d %d개 서비스, 누적대기시간 %d, 평균서비스시간 %f\n", i, totalService[i], cumulativeTime[i], averageTime);
    }
    printf("취소된 주문 %d 개\n", cancledOrder);
    printf("서버1과 서버2 휴식 시간 : %d, %d\n", server1.restTime, server2.restTime);
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
    if (isFull(*q))
        printf("Queue is full\n");
    else
    {
        q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
        q->data[q->rear] = e;
    }
}

ELEMENT dequeue(QUEUE *q)
{
    if (isEmpty(*q))
        printf("Queue is empty\n");
    else
    {
        q->front = (q->front + 1) % MAX_QUEUE_SIZE;
        return q->data[q->front];
    }
}

int menuRequired(int menuNum)
{
    switch (menuNum)
    {
    case 0:
        return 5;
    case 1:
        return 10;
    case 2:
        return 15;
    case 3:
        return 20;
    case 4:
        return 25;

    default:
        return -1;
    }
}
#include "queue.h"

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

int qisEmpty(QUEUE q)
{
    if (q.front == q.rear)
        return 1;
    else
        return 0;
}

void enqueue(QUEUE *q, qELEMENT e)
{
    if (isFull(*q))
        printf("Queue is full\n");
    else
    {
        q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
        q->data[q->rear] = e;
    }
}

qELEMENT dequeue(QUEUE *q)
{
    if (qisEmpty(*q))
        printf("Queue is empty\n");
    else
    {
        q->front = (q->front + 1) % MAX_QUEUE_SIZE;
        return q->data[q->front];
    }
}
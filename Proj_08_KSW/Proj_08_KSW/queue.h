#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 10000

typedef struct _qELEMENT
{
    long data;
    int time;
} qELEMENT;

typedef struct _QUEUE
{
    qELEMENT data[MAX_QUEUE_SIZE];
    int front;
    int rear;
} QUEUE;

void initQueue(QUEUE *);
int isFull(QUEUE);
int qisEmpty(QUEUE);
void enqueue(QUEUE *, qELEMENT);
qELEMENT dequeue(QUEUE *);

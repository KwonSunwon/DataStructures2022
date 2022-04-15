#include <stdio.h>
#include <stdlib.h>

#define WAIT_QUEUE_SIZE 1000
#define READY_QUEUE_SIZE 10
#define NUM_JOBS 1000
#define TIME_SLOT 10

typedef struct DATA_ELEMENT
{
    int job_id;
    int priority;
    int arrival_time;
    int run_time;
    int remaining_time;
    int run_count;
} data_el;

typedef struct _QUEUE
{
    data_el *data;
    int front;
    int rear;
} QUEUE;

void init(QUEUE *);
void init_ready_queue(QUEUE *);

int job_create(int *, int, QUEUE *, int);

int main()
{
    int jobs[NUM_JOBS][3];
    int remain_job_count = NUM_JOBS;
    int processing_time = 0;

    // 테스트할 JOB 생성
    for (int i = 0; i < NUM_JOBS; i++)
    {
        jobs[i][0] = rand() % 10;            // priority;
        jobs[i][1] = rand();                 // arrival_time;
        jobs[i][2] = (rand() % 10 + 5) * 10; // run_time
    }

    // 대기 큐와 준비 큐 초기화
    QUEUE wq;
    QUEUE rq;
    init(&wq);
    init_ready_queue(&rq);

    // 프로세스 스케쥴링
    while (1)
    {
        remain_job_count -= job_create(jobs, remain_job_count, &wq, processing_time);
        job_dispatcher(&wq, &rq);
        job_process(&wq, &rq, processing_time);
        processing_time++;
        if (remain_job_count == 0 && is_empty(&wq) &&
            is_ready_queue_empty(&rq))
            break;
    }

    // 큐 메모리 해제
    finalize(&wq);
    finalize(&rq);
}

void init(QUEUE *wp)
{
    wp->data = (data_el *)malloc(sizeof(data_el) * WAIT_QUEUE_SIZE);
    wp->front = 0;
    wp->rear = 0;
}

void init(QUEUE *rq)
{
    rq->data = (data_el *)malloc(sizeof(data_el) * READY_QUEUE_SIZE);
    rq->front = 0;
    rq->rear = 0;
}
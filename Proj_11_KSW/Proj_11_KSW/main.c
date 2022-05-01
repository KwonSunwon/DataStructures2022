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
    int count;
} QUEUE;

typedef struct _READY_QUEUE
{
    data_el data[READY_QUEUE_SIZE];
    int front;
    int rear;
} READY_QUEUE;

void init(QUEUE *);
void init_ready_queue(QUEUE *);

int is_empty(QUEUE *);
int is_ready_queue_empty(READY_QUEUE *);

int is_full(QUEUE *);
int is_ready_queue_full(READY_QUEUE *);

void enqueue(QUEUE *, data_el);
void ready_enqueue(READY_QUEUE *, data_el);

data_el dequeue(QUEUE *);
data_el ready_dequeue(READY_QUEUE *);

int job_create(int[][3], int, QUEUE *, int);
void job_dispatcher(QUEUE *, READY_QUEUE *);
void job_process(QUEUE *, READY_QUEUE *, int);

void finalize(QUEUE *);

int main()
{
    int jobs[NUM_JOBS][4];
    int remain_job_count = NUM_JOBS;
    int processing_time = 0;

    data_el data;
    data.job_id = -1;

    // 테스트할 JOB 생성
    for (int i = 0; i < NUM_JOBS; i++)
    {
        jobs[i][0] = rand() % 10;            // priority;
        jobs[i][1] = rand();                 // arrival_time;
        jobs[i][2] = (rand() % 10 + 5) * 10; // run_time
        jobs[i][3] = i;
    }

    // 대기 큐와 준비 큐 초기화
    QUEUE wq;
    READY_QUEUE rq;

    init(&wq);
    init_ready_queue(&rq);

    // 프로세스 스케쥴링
    while (1)
    {
        remain_job_count -= job_create(jobs, remain_job_count, &wq, processing_time);
        job_dispatcher(&wq, &rq);
        job_process(&wq, &rq, processing_time, &data);
        processing_time++;
        if (remain_job_count == 0 && is_empty(&wq) && is_ready_queue_empty(&rq))
            break;
    }

    // 큐 메모리 해제
    finalize(&wq);
}

void init(QUEUE *wq)
{
    wq->data = (data_el *)malloc(sizeof(data_el) * WAIT_QUEUE_SIZE);
    wq->count = 0;
}
void init_ready_queue(READY_QUEUE *rq)
{
    rq->front = 0;
    rq->rear = 0;
}

int is_empty(QUEUE *wq)
{
    if (wq->count == 0)
        return 1;
    else
        return 0;
}
int is_ready_queue_empty(READY_QUEUE *rq)
{
    if (rq->front == rq->rear)
        return 1;
    else
        return 0;
}

int is_full(QUEUE *wq)
{
    if (wq->count == WAIT_QUEUE_SIZE)
        return 1;
    else
        return 0;
}
int is_ready_queue_full(READY_QUEUE *rq)
{
    if (rq->front == (rq->rear + 1) % READY_QUEUE_SIZE)
        return 1;
    else
        return 0;
}

void enqueue(QUEUE *wq, data_el data)
{
    if (wq->count == 0)
    {
        wq->data[wq->count++] = data;
    }
    else if (!is_full(wq))
    {
        int idx = 0;
        while (idx != wq->count)
        {
            if (wq->data[idx].priority > data.priority)
                break;
            ++idx;
        }

        if (idx == wq->count)
            wq->data[wq->count++] = data;
        else
        {
            for (int i = wq->count; i > idx - 1; --i)
                wq->data[i + 1] = wq->data[i]; // 이부분에서 제대로 참조가 안되어서 옮겨지지 않고 쓰레기 값이 들어감
            wq->data[idx] = data;
            ++wq->count;
        }
    }
}
void ready_enqueue(READY_QUEUE *rq, data_el data)
{
    if (!is_ready_queue_full(rq))
    {
        rq->rear = (rq->rear + 1) % READY_QUEUE_SIZE;
        rq->data[rq->rear] = data;
    }
}

data_el dequeue(QUEUE *wq)
{
    if (!is_empty(wq))
    {
        data_el data;
        data = wq->data[0];
        for (int i = 0; i < wq->count - 1; ++i)
            wq->data[i] = wq->data[i + 1];
        --wq->count;
        return data;
    }
}
data_el ready_dequeue(READY_QUEUE *rq)
{
    if (!is_ready_queue_empty(rq))
    {
        rq->front = (rq->front + 1) % READY_QUEUE_SIZE;
        return rq->data[rq->front];
    }
}

void finalize(QUEUE *wq)
{
    free(wq->data);
}

int job_create(int jobs[][4], int reamain_job_count, QUEUE *wq, int processing_time)
{
    if (reamain_job_count == 0)
        return 0;

    data_el data;
    int num_jobs = 0;
    for (int i = 0; i < NUM_JOBS; ++i)
    {
        if (jobs[i][1] == processing_time)
        {
            data.priority = jobs[i][0];
            data.arrival_time = jobs[i][1];
            data.run_time = jobs[i][2];
            data.remaining_time = TIME_SLOT;
            data.run_count = 0;
            data.job_id = jobs[i][3];
            enqueue(wq, data);
            ++num_jobs;
        }
    }
    return num_jobs;

    // int idx = NUM_JOBS - reamain_job_count;
    // while (!is_full(wq))
    // {
    //     data.priority = jobs[idx][0];
    //     data.arrival_time = jobs[idx][1];
    //     data.remaining_time = jobs[idx][2];
    //     data.run_count = 0;
    //     data.run_time = 0;
    //     data.job_id = idx;
    //     // printf("%d\n", idx);

    //     enqueue(wq, data);
    //     ++idx;
    // }
    // return idx;
}

void job_dispatcher(QUEUE *wq, READY_QUEUE *rq)
{
    while (1)
    {
        if (is_empty(wq))
            break;
        else if (is_ready_queue_full(rq))
            break;
        else
        {
            data_el data = dequeue(wq);
            ready_enqueue(rq, data);
        }
    }
}

void job_process(QUEUE *wq, READY_QUEUE *rq, int processing_time, data_el *data)
{
    if (!is_ready_queue_empty(rq))
    {
        if (data->job_id == -1)
            *data = ready_dequeue(rq);

        if (data->run_time != 0)
        {
            --data->run_time;
            --data->remaining_time;
        }

        if (data->run_time == 0)
        {
            printf("시간 %d : 작업 : %d 종료", processing_time, data->job_id);
            printf("(도착시간 : %d, 실행시간 : %d, 실행횟수 : %d,", data->arrival_time, data->run_count * TIME_SLOT, data->run_count);
            printf(" 지연시간 : %d, 최종우선순위 : %d)\n", (processing_time - data->arrival_time), data->priority);
            *data = ready_dequeue(rq);
        }
        else if (data->remaining_time == 0)
        {
            ++data->priority;
            ++data->run_count;
            data->remaining_time = TIME_SLOT;
            enqueue(wq, *data);
            *data = ready_dequeue(rq);
        }
        // data = ready_dequeue(rq);
        // ++data.run_count;
        // for (int i = 0; i < TIME_SLOT; ++i)
        // {
        //     --data.remaining_time;
        //     ++data.run_time;
        //     if (data.remaining_time == 0)
        //         break;
        // }

        // if (data.remaining_time == 0)
        // {
        //     printf("시간 %d : 작업 : %d 종료", processing_time, data.job_id);
        //     printf("(도착시간 : %d, 실행시간 : %d, 실행횟수 : %d,", data.arrival_time, data.run_time, data.run_count);
        //     printf(" 지연시간 : %d, 최종우선순위 : %d)\n", (processing_time - data.arrival_time), data.priority);
        // }
        // else
        // {
        //     ++data.priority;
        //     enqueue(wq, data);
        // }
    }
}
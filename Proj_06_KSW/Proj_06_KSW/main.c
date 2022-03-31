#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // isdigit() 사용

#define PROB 2

#define MAX_STACK_NUMBER 50

#if PROB == 1
typedef union _ELEMENT
{
    int operand;
    char operator;
} ELEMENT; // union

#elif PROB == 2
typedef struct _ELEMENT
{
    int row;
    int col;
} ELEMENT;

#endif

typedef struct _STACK
{
    ELEMENT data[MAX_STACK_NUMBER];
    int top;
} STACK;

void init(STACK *);
void push(STACK *, ELEMENT);
ELEMENT pop(STACK *);
int isEmpty(STACK);
ELEMENT peek(STACK);

#if PROB == 1

int prec(char);
int changePostfix(char *, char[]);
int calculatePostfix(char *);

int main(void)
{
    char *expr = "10 + 20 * (20 + 10) / 100 +5 -3";

    char *changedExpr = (char *)malloc(strlen(expr) + 1);
    memset(changedExpr, 0, sizeof(char) * strlen(expr) + 1);

    printf("%s\n", expr);
    if (changePostfix(expr, changedExpr))
    {
        printf("%s\n", changedExpr);
        printf("수식 오류\n");
    }
    else
    {
        printf("%s\n", changedExpr);
        printf("연산 결과 : %d\n", calculatePostfix(changedExpr));
    }

    free(changedExpr);
}

int prec(char ch)
{
    switch (ch)
    {
    case '(':
        return 0;
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    }
}

int changePostfix(char *expr, char changedExpr[])
{
    STACK stk;
    init(&stk);

    int error = 0;
    ELEMENT tmp;

    int idx = 0;
    for (int i = 0; i < strlen(expr); ++i)
    {
        tmp.operator= expr[i];

        switch (tmp.operator)
        {
        case ' ':
            changedExpr[idx++] = tmp.operator;
            if (isdigit(expr[i - 1]) == isdigit(expr[i + 1]) && !(expr[i - 1] == ')' || expr[i + 1] == '('))
                error = 1;
            if ((isdigit(expr[i - 1]) && expr[i + 1] == '(') || (isdigit(expr[i + 1]) && expr[i - 1] == ')'))
                error = 1;
            break;

        case '+':
        case '-':
        case '*':
        case '/':
            while (prec(peek(stk).operator) >= prec(tmp.operator) && !isEmpty(stk))
            {
                changedExpr[idx++] = pop(&stk).operator;
            }
            push(&stk, tmp);
            break;

        case '(':
            push(&stk, tmp);
            break;

        case ')':
            while (peek(stk).operator!= '(')
                changedExpr[idx++] = pop(&stk).operator;
            pop(&stk);
            break;

        default:
            changedExpr[idx++] = tmp.operator;
            break;
        }
    }

    while (!isEmpty(stk))
        changedExpr[idx++] = pop(&stk).operator;

    return error;
}

int calculatePostfix(char *expr)
{
    STACK stk;
    init(&stk);

    ELEMENT tmp;
    ELEMENT first;
    ELEMENT second;
    ELEMENT result;

    int i = 0;

    while (expr[i] != '\0')
    {
        if (expr[i] == ' ')
            ++i;
        else if (isdigit(expr[i]))
        {
            tmp.operand = 0;
            while (isdigit(expr[i]))
                tmp.operand = tmp.operand * 10 + (expr[i++] - '0');
            push(&stk, tmp);
        }
        else
        {
            second.operand = pop(&stk).operand;
            first.operand = pop(&stk).operand;
            result.operand = 0;
            switch (expr[i])
            {
            case '+':
                result.operand = first.operand + second.operand;
                break;
            case '-':
                result.operand = first.operand - second.operand;
                break;
            case '*':
                result.operand = first.operand * second.operand;
                break;
            case '/':
                result.operand = first.operand / second.operand;
                break;
            }
            push(&stk, result);
            ++i;
        }
    }

    return pop(&stk).operand;
}

#elif PROB == 2

#define MAZE_SIZE 9
char maze[MAZE_SIZE][MAZE_SIZE] = {
    {'1', '1', '1', '1', '1', '1', '1', '0', '1'},
    {'e', '0', '0', '0', '0', '0', '0', '0', '1'},
    {'1', '0', '1', '0', '1', '1', '0', '1', '0'},
    {'1', '0', '0', '1', '0', '0', '0', '1', '0'},
    {'1', '0', '1', '1', '0', '1', '1', '1', '0'},
    {'1', '0', '1', '0', '1', 'x', '1', '0', '0'},
    {'1', '0', '0', '0', '1', '0', '1', '0', '1'},
    {'1', '0', '1', '0', '0', '0', '0', '0', '1'},
    {'1', '0', '1', '0', '1', '1', '1', '1', '1'},
};

// 마지막의 최적의 경로를 표시하기 위해서는
// stack 에 바로 직전의 위치를 계속 저장
// 각 분기에서 갈 수 있는 모든 곳의 좌표를 저장하지 않음.

// 탐색해서 시작위치 찾기 - 첫 위치 스택 push
// 이동 가능한 곳을 탐색해서 처음 탐색된 곳으로 이동 - 이동 위치 스택 push
// 위 반복중에 더 이상 이동이 불가능 하면 스택 하나를 pop
// pop 한 위치에서 이동할 곳이 없다면 이동할 수 있는 곳이 나올 때까지 pop
// 이동 가능한 길이 나오면 2번 줄부터 반복
// 더 이상 갈 수 있는 길이 없고 목적지를 찾지 못 했다면 실패
// 위 과정 중간에 목적지에 도달하면 성공

int main(void)
{
    STACK stk;
    init(&stk);

    int mazeSuccess = 0;

    ELEMENT idx = {0, 0};
    while (maze[idx.row][idx.col] != 'e')
    {
        ++idx.col;
        if (idx.col == MAZE_SIZE)
        {
            ++idx.row;
            if (idx.row == MAZE_SIZE)
            {
                printf("시작지점 없음");
                return 1;
            }
            idx.col = 0;
        }
    }

    push(&stk, idx);

    while (!isEmpty(stk))
    {
        idx = peek(stk);
        if (maze[idx.row][idx.col] == 'x')
        {
            mazeSuccess = 1;
            break;
        }
        else if (maze[idx.row][idx.col] != '.')
            maze[idx.row][idx.col] = '.';

        if ((maze[idx.row][idx.col + 1] == '0' || maze[idx.row][idx.col + 1] == 'x') && idx.col + 1 != MAZE_SIZE)
        {
            ++idx.col;
            push(&stk, idx);
        }
        else if ((maze[idx.row + 1][idx.col] == '0' || maze[idx.row + 1][idx.col] == 'x') && idx.row + 1 != MAZE_SIZE)
        {
            ++idx.row;
            push(&stk, idx);
        }
        else if ((maze[idx.row][idx.col - 1] == '0' || maze[idx.row][idx.col - 1] == 'x') && idx.col - 1 != -1)
        {
            --idx.col;
            push(&stk, idx);
        }
        else if ((maze[idx.row - 1][idx.col] == '0' || maze[idx.row - 1][idx.col] == 'x') && idx.row - 1 != -1)
        {
            --idx.row;
            push(&stk, idx);
        }
        else
        {
            pop(&stk);
        }
    }

    if (mazeSuccess)
    {
        idx.col = 0;
        idx.row = 0;
        printf("-------미로-------\n");
        for (int i = 0; i < MAZE_SIZE * MAZE_SIZE; ++i)
        {
            printf("%c ", maze[idx.row][idx.col++]);
            if (idx.col == MAZE_SIZE)
            {
                ++idx.row;
                idx.col = 0;
                printf("\n");
            }
        }
        printf("-------미로-------\n");

        int stackSize = stk.top;

        ELEMENT *route = (ELEMENT *)malloc(sizeof(ELEMENT) * (stackSize + 1));
        for (int i = stackSize; i > -1; --i)
        {
            route[i] = pop(&stk);
        }

        printf("경로 : \n(row col)\n");
        for (int i = 0; i < stackSize + 1; ++i)
        {
            printf(" (%d   %d)\n", route[i].row, route[i].col);
        }
    }
    else
        printf("탐색 실패\n");
}

#endif

void init(STACK *s)
{
    s->top = -1;
}

void push(STACK *s, ELEMENT e)
{
    s->data[++s->top] = e;
}

ELEMENT pop(STACK *s)
{
    return s->data[s->top--];
}

int isEmpty(STACK s)
{
    if (s.top == -1)
        return 1;
    else
        return 0;
}

ELEMENT peek(STACK s)
{
    return s.data[s.top];
}
#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <ctype.h> // isdigit() 사용
#include "stack.h"

#define PROB 1

#ifdef PROB == 1

int prec(char);
int changePostfix(char *, char[]);

int main(void)
{
    char *expr = "100 + 11 + 20 * (20 + 10) / 100 +5 -3";

    char *changedExpr = (char *)malloc(strlen(expr) + 1);
    memset(changedExpr, 0, sizeof(char) * strlen(expr) + 1);

    if (changePostfix(expr, changedExpr))
    {
        printf("%s\n", expr);
        printf("수식 오류\n");
        return 0;
    }
    printf("%s\n", expr);

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

#elif PROB == 2

#define MAZE_SIZE 6
char maze[MAZE_SIZE][MAZE_SIZE] = {
    {'1', '1', '1', '1', '1', '1'},
    {'e', '0', '1', '0', '0', '1'},
    {'1', '0', '0', '0', '1', '1'},
    {'1', '0', '1', '0', '1', '1'},
    {'1', '0', '1', '0', '0', 'x'},
    {'1', '1', '1', '1', '1', '1'},
}

// 마지막의 최적의 경로를 표시하기 위해서는
// stack 에 바로 직전의 위치를 계속 저장
// 각 분기에서 갈 수 있는 모든 곳의 좌표를 저장하지 않음.

#endif
#include <ctype.h> // isdigit() 사용
#include "stack.h"

#define PROB 1;

#ifdef PROB == 1
int prec(char);
int changePostfix(char *);

int main(void)
{
    char *expr = "100 + 11 20 * (20 + 10) / 100 +5 -3";
    if (changePostfix(expr))
    {
        printf("%s\n", expr);
        printf("수식 오류\n");
        return 0;
    }
}

int prec(char ch)
{
    switch (ch)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    }
}

int changePostfix(char *expr)
{
    STACK stk;
    init(&stk);
    int error = 0;
    char *chagedExpr = (char *)malloc(strlen(expr) + 1);

    int idx = 0;
    while (expr[idx] != '\0')
    {
        char tmp = expr[idx];
        if (tmp == ' ')
        {
            if (isdigit(expr[idx - 1]) == isdigit(expr[idx + 1]))
                error = 1;
        }
        else if (isdigit(tmp))
        {
            chagedExpr[idx++] = tmp;
            continue;
        }
        else
        {
            switch (tmp)
            {
            case '+':
            case '-':
            case '*':
            case '/':
                while (prec(peek(stk).operator) >= prec(tmp))
                {
                    chagedExpr[idx++] = pop(&stk).operator;
                }
                push(&stk, tmp);
                break;
            case '(':
                break;
            case ')':
                break;
            default:
                break;
            }
        }
    }

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
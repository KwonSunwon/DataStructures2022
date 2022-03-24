// 미로 찾기 알고리즘 -> 스택을 많이 활용

#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_NUMBER 100

typedef struct _ELEMENT
{
    char bracket;
    int pos;
} element;

typedef struct _STACK
{
    element data[MAX_STACK_NUMBER];
    int top;
} stack;

void init(stack *);
void push(stack *, element);
element pop(stack *);
int isEmpty(stack);

int checkBracket(stack *, element *, int, char);

int main()
{
    stack stk;
    char *expr = "A(x) = 24.5 * (x + func(x, y)) * (r * r * 3.14) / [7 % 10 * sqrt(25)];";
    element temp;
    int errorPos[MAX_STACK_NUMBER];
    int errorCount = 0;

    init(&stk);

    int i = 0;
    while (expr[i] != '\0')
    {
        switch (expr[i])
        {
        case '(':
        case '[':
        case '{':
            temp.bracket = expr[i];
            temp.pos = i;
            push(&stk, temp);
            break;

        case ')':
            if (checkBracket(&stk, &temp, i, expr[i]) == 0)
                break;
            else
            {
                // 오류난 위치 전달하는거 만들면됨.
            }
        case ']':
            checkBracket(&stk, &temp, i, expr[i]);
            break;
        case '}':
            checkBracket(&stk, &temp, i, expr[i]);
            break;

        default:
            break;
        }

        ++i;
    }
    printf("%s\n", expr);
    if (isEmpty(stk) != 1 || errorCount > 0) // 괄호의 개수가 맞지 않는 경우, 이미 오류가 존재하는 경우
    {
        printf(" => 괄호검사실패 ");
        for (int i = 0; i < stk.top; ++i)
            printf("%d ", pop(&stk).pos);
        for (int i = 0; i < errorCount; ++i)
            printf("%d ", errorPos[i]);
        printf("위치\n");
    }
    else
        printf(" => 괄호검사성공");
}

void init(stack *s)
{
    s->top = -1;
}

void push(stack *s, element e)
{
    s->data[++s->top] = e;
}

element pop(stack *s)
{
    return s->data[s->top--];
}

int isEmpty(stack s)
{
    if (s.top == -1)
        return 1;
    else
        return 0;
}

int checkBracket(stack *s, element *e, int i, char bracket)
{
    if (isEmpty(*s) == 1) // 우 괄호가 먼저 나오는 경우
        return 1;

    *e = pop(s);
    if (e->bracket != bracket) // 괄호의 종류가 다른 경우
    {
        return 1;
    }
    else
        return 0;
}
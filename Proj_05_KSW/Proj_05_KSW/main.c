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

int checkBracket(stack *, element *, char);

int main()
{
    stack stk;
    char *expr = "A(x) = 24.5 * (x + func(x, y)) * (r * r * 3.14) / [ 7 % 10 * sqrt(25)];";
    element temp;

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
            temp.pos = i + 1;
            push(&stk, temp);
            break;

        case ')':
        case ']':
        case '}':
            switch (checkBracket(&stk, &temp, expr[i]))
            {
            case 0:
                break;
            case 1:
                printf("%s\n", expr);
                printf(" => 괄호검사실패 %d 위치\n", i + 1);
                return;
            case 2:
                printf("%s\n", expr);
                printf(" => 괄호검사실패 %d, %d 위치\n", temp.pos, i + 1);
                return;
            }
        default:
            break;
        }

        ++i;
    }
    printf("%s\n", expr);
    if (isEmpty(stk) != 1) // 괄호의 개수가 맞지 않는 경우, 이미 오류가 존재하는 경우
    {
        printf(" => 괄호검사실패 ");
        for (int i = 0; i < stk.top + 1; ++i)
            printf("%d ", pop(&stk).pos);
        printf("위치\n");
    }
    else
        printf(" => 괄호검사성공\n");
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

int checkBracket(stack *s, element *e, char bracket)
{
    if (isEmpty(*s) == 1) // 우 괄호가 먼저 나오는 경우
        return 1;

    *e = pop(s);
    switch (bracket)
    {
    case ')':
        bracket = '(';
        break;
    case ']':
        bracket = '[';
        break;
    case '}':
        bracket = '{';
        break;
    }
    if (e->bracket != bracket) // 괄호의 종류가 다른 경우
    {
        return 2;
    }
    else
        return 0;
}
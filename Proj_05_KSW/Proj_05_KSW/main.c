// �̷� ã�� �˰��� -> ������ ���� Ȱ��

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
                // ������ ��ġ �����ϴ°� ������.
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
    if (isEmpty(stk) != 1 || errorCount > 0) // ��ȣ�� ������ ���� �ʴ� ���, �̹� ������ �����ϴ� ���
    {
        printf(" => ��ȣ�˻���� ");
        for (int i = 0; i < stk.top; ++i)
            printf("%d ", pop(&stk).pos);
        for (int i = 0; i < errorCount; ++i)
            printf("%d ", errorPos[i]);
        printf("��ġ\n");
    }
    else
        printf(" => ��ȣ�˻缺��");
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
    if (isEmpty(*s) == 1) // �� ��ȣ�� ���� ������ ���
        return 1;

    *e = pop(s);
    if (e->bracket != bracket) // ��ȣ�� ������ �ٸ� ���
    {
        return 1;
    }
    else
        return 0;
}
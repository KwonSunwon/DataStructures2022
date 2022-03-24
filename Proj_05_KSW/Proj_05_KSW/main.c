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
                printf(" => ��ȣ�˻���� %d ��ġ\n", i + 1);
                return;
            case 2:
                printf("%s\n", expr);
                printf(" => ��ȣ�˻���� %d, %d ��ġ\n", temp.pos, i + 1);
                return;
            }
        default:
            break;
        }

        ++i;
    }
    printf("%s\n", expr);
    if (isEmpty(stk) != 1) // ��ȣ�� ������ ���� �ʴ� ���, �̹� ������ �����ϴ� ���
    {
        printf(" => ��ȣ�˻���� ");
        for (int i = 0; i < stk.top + 1; ++i)
            printf("%d ", pop(&stk).pos);
        printf("��ġ\n");
    }
    else
        printf(" => ��ȣ�˻缺��\n");
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
    if (isEmpty(*s) == 1) // �� ��ȣ�� ���� ������ ���
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
    if (e->bracket != bracket) // ��ȣ�� ������ �ٸ� ���
    {
        return 2;
    }
    else
        return 0;
}
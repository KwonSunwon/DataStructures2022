#include "stack.h"

void init(STACK *s)
{
    s->top = -1;
}

void push(STACK *s, int e)
{
    s->data[++s->top] = e;
}

int pop(STACK *s)
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

int peek(STACK s)
{
    return s.data[s.top];
}
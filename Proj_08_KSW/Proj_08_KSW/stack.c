#include "stack.h"

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
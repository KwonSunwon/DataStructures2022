#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_NUMBER 100

typedef char ELEMENT;

typedef struct _STACK
{
    ELEMENT data[MAX_STACK_NUMBER];
    int top;
} STACK;

void init(STACK *);
void push(STACK *, ELEMENT);
ELEMENT pop(STACK *);
int isEmpty(STACK);
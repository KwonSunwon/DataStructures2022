#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 10000

typedef int ELEMENT;

typedef struct _STACK
{
    int data[MAX_STACK_SIZE];
    int top;
} STACK;

void init(STACK *);
void push(STACK *, ELEMENT);
ELEMENT pop(STACK *);
int isEmpty(STACK);
ELEMENT peek(STACK);

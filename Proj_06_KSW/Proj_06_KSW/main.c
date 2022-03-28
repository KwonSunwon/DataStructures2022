#include "stack.h"

#define PROB 1;

#ifdef PROB == 1
void changePostfix(char *);

int main(void)
{
    char *expr = "100 + 11 20 * (20 + 10) / 100 +5 -3";
    changePostfix(expr);
}

void changePostfix(char *expr)
{
    STACK stack;
    int errorChecker;
    char *chagedExpr = (char *)malloc(strlen(expr) + 1);

    int idx = 0;
    while (expr[idx] != '\0')
    {

    }
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

#endif
#include <stdio.h>
#include <assert.h>
#include <string.h>

const int CAPOCITY = 5;

struct Stack
{
    int data[CAPOCITY];
    size_t size;
};

int stackCtor (Stack* stack);
int stackPush (Stack* stack, int value);
int stackPop (Stack* stack, int* x);
int stackDtor (Stack* stack);
void printStack(Stack* stack);

int main ()
{
    struct Stack st;
    stackCtor (&st);

    stackPush (&st, 10);
    stackPush (&st, 15);
    stackPush (&st, 20);

    printStack (&st);

    int x = 0;
    stackPop (&st, &x);
    printf ("%d\n", x);

    printStack (&st);

    stackDtor (&st);

    return 0;
}



int stackCtor (Stack* stack)
{
    assert (stack);

    memset (stack->data, 0, sizeof (stack->data));
    stack->size = 0;

    return 0;
}

int stackPush (Stack* stack, int value)
{
    assert (stack);

    if (stack->size > CAPOCITY)
    {
        printf ("Out of memory\n");
        return 1;
    }

    stack->data[stack->size++] = value;

    return 0;
}

int stackPop (Stack* stack, int* x)
{
    assert (stack);

    if (stack->size == 0)
    {
        printf ("Underflow\n");
        return 2;
    }

    *x = --stack->size;

    return 0;
}

int stackDtor (Stack* stack)
{
    assert (stack);

    memset (stack->data, 0, sizeof (stack->data));
    stack->size = -1;

    return 0;
}

void printStack (Stack* stack)
{
    assert (stack);

    for (int num = 0; num < stack->size; num++)
    {
        printf ("%d\n", stack->data[num]);
    }
}

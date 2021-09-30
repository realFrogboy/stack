#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

enum ERRORS
{
    SUCCESS         = 0,
    STACK_UNDERFLOW = 10101,
    STACK_OVERFLOW  = 10201,
    ALLOC_ERROR     = 10301,
    REALLOC_ERROR   = 10401
};

const int START_STACK_SIZE = 2;
const int COEFFICIENT = 2;

struct Stack
{
    int *data;
    size_t capocity;
    size_t size;
};

int stackCtor (Stack* stack);
int stackPush (Stack* stack, int value);
int stackPop (Stack* stack, int* x);
int stackDtor (Stack* stack);
void printStack(Stack* stack);
int reallocate (Stack* stack, size_t newSize);

int main ()
{
    struct Stack st;
    stackCtor (&st);
    printStack (&st);
    printf ("%d --- %d\n", st.size, st.capocity);

    stackPush (&st, 10);
    printStack (&st);
    printf ("%d --- %d\n", st.size, st.capocity);

    stackPush (&st, 15);
    printStack (&st);
    printf ("%d --- %d\n", st.size, st.capocity);

    stackPush (&st, 20);
    printStack (&st);
    printf ("%d --- %d\n", st.size, st.capocity);

    int x = 0;
    stackPop (&st, &x);
    printf ("%d\n", x);
    printStack (&st);
    printf ("%d --- %d\n", st.size, st.capocity);

    //stackDtor (&st);

    return SUCCESS;
}



int stackCtor (Stack* stack)
{
    assert (stack);

    stack->capocity = START_STACK_SIZE;
    stack->size = 0;

    stack->data = (int*) calloc (stack->capocity, sizeof (int));
    if (stack->data == NULL)
    {
        printf ("Can't alloc memory\n");
        return ALLOC_ERROR;
    }

    return SUCCESS;
}

int stackPush (Stack* stack, int value)
{
    assert (stack);

    if (stack->size >= stack->capocity)
    {
        reallocate (stack, stack->capocity * COEFFICIENT);
    }

    *(stack->data + stack->size * sizeof (int)) = value;
    stack->size++;

    return SUCCESS;
}

int stackPop (Stack* stack, int* x)
{
    assert (stack);

    if (stack->size == 0)
    {
        printf ("Stack underflow\n");
        return STACK_UNDERFLOW;
    }

    *x = --stack->size;

    if (stack->size <= stack->capocity/COEFFICIENT)
    {
        reallocate (stack, stack->capocity/COEFFICIENT);
    }


    return SUCCESS;
}

int stackDtor (Stack* stack)
{
    assert (stack);

    //free (stack->data);
    stack->size = -1;

    return SUCCESS;
}

void printStack (Stack* stack)
{
    assert (stack);

    for (int num = 0; num < stack->size; num++)
    {
        printf ("%d\n", *(stack->data + num * sizeof (int)));
    }
}

int reallocate (Stack* stack, size_t newSize)
{
    stack->capocity = newSize;
    stack->data = (int*) realloc (stack->data, stack->capocity);
    if (stack->data == NULL)
        {
            printf ("Can't realloc memory\n");
            return ALLOC_ERROR;
        }

    return SUCCESS;
}



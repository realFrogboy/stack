#include "stack.h"

int stackCtor (Stack* st)
{
    assert (st);

    st->capocity = START_STACK_SIZE;
    st->Size = 1;

    st->data = (int*) calloc (st->capocity, sizeof (int));
    if (st->data == NULL)
    {
        printf ("%s:%d %s\n", __FILE__, __LINE__, "Can't alloc memory.\n");
        return ALLOC_ERROR;
    }

    return SUCCESS;
}


//-----------------------------------------------------------------------------


int stackPush (Stack* st, int value)
{
    int error = stackOK (st);
    if (error != 0)
    {
        stackDump (__FILE__, __LINE__, error);
        return error;
    }

    if (st->Size >= st->capocity)
    {
        reallocate (st, st->capocity * COEFFICIENT);
    }

    *(st->data + st->Size * sizeof (int)) = value;
    st->Size++;

    return SUCCESS;
}


//-----------------------------------------------------------------------------


int stackPop (Stack* st, int* x)
{
    int error = stackOK (st);
    if (error != 0)
    {
        stackDump (__FILE__, __LINE__, error);
        return error;
    }

    *x = --st->Size;

    if (st->Size <= st->capocity/COEFFICIENT)
    {
        reallocate (st, st->capocity/COEFFICIENT);
    }


    return SUCCESS;
}


//-----------------------------------------------------------------------------


int stackDtor (Stack* st)
{
    int error = stackOK (st);
    if (error != 0)
    {
        stackDump (__FILE__, __LINE__, error);
        return error;
    }

    free (st->data);
    st->Size = 0;

    return SUCCESS;
}


//-----------------------------------------------------------------------------


int printStack (Stack* st)
{
    int error = stackOK (st);
    if (error != 0)
    {
        stackDump (__FILE__, __LINE__, error);
        return error;
    }

    for (unsigned num = st->Size; num >= 1; num--)
    {
        printf ("%d\n", *(st->data + num * sizeof (int)));
    }

    return 0;
}


//-----------------------------------------------------------------------------


int reallocate (Stack* st, size_t newSize)
{
    int error = stackOK (st);
    if (error != 0)
    {
        stackDump (__FILE__, __LINE__, error);
        return error;
    }

    st->capocity = newSize;
    st->data = (int*) realloc (st->data, st->capocity);
    if (st->data == NULL)
        {
            printf ("%s:%d %s\n", __FILE__, __LINE__, "Can't realloc memory.\n");
            return ALLOC_ERROR;
        }

    return SUCCESS;
}


//-----------------------------------------------------------------------------


int stackOK (const Stack* st)
{
    if (!st) return VOID_STACK;
    if (st->Size < 0) return STACK_UNDERFLOW;
    if (st->capocity < st->Size) return STACK_OVERFLOW;

    return 0;
}


//-----------------------------------------------------------------------------


void stackDump (const char* name, int line, int error)
{
    switch (error)
    {
        case STACK_UNDERFLOW:
            logInfo (stdout, name, line, "Stack Underflow\n");
            break;

        case STACK_OVERFLOW:
            logInfo (stdout, name, line, "Stack Overflow\n");
            break;

        case VOID_STACK:
            logInfo (stdout, name, line, "Stack is NULL\n");

    }
}


//-----------------------------------------------------------------------------


void logInfo (FILE* ptrfile, const char* file, int line, const char* errorCode)
{
    fprintf (ptrfile, "%s:%d %s\n", file, line, errorCode);
}


//-----------------------------------------------------------------------------


void cleanBuffer ()
{
    while (getchar () != '\n');
}


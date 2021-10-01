//enum
//logging
//

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

//#define log_info (...) \
        fprintf(fd,"%s:%d %s\n", file, line);

enum ERRORS
{
    SUCCESS            = 0,
    STACK_UNDERFLOW    = 10101,
    STACK_OVERFLOW     = 10201,
    ALLOC_ERROR        = 10301,
    REALLOC_ERROR      = 10401,
    VOID_STACK         = 10501
};

const int START_STACK_SIZE = 2;
const int COEFFICIENT = 2;

struct Stack
{
    int *data;
    size_t capocity;
    size_t Size;
};

int stackCtor (Stack* st);
int stackPush (Stack* st, int value);
int stackPop (Stack* st, int* x);
int stackDtor (Stack* st);
int printStack(Stack* st);
int reallocate (Stack* st, size_t newSize);
int stackOK (const Stack* st);
void stackDump (int error);
void logInfo (FILE* ptrfile, const char* file, int line, const char* errorCode);

int main ()
{
    int error = 0;

    struct Stack st;
    error = stackCtor (&st);
    if (error != 0) return error;
    printStack (&st);
    printf ("%d --- %d\n", st.Size, st.capocity);

    error = stackPush (&st, 10);
    printStack (&st);
    if (error != 0) return error;
    printf ("%d --- %d\n", st.Size, st.capocity);

    error = stackPush (&st, 15);
    if (error != 0) return error;
    printStack (&st);
    printf ("%d --- %d\n", st.Size, st.capocity);

    error = stackPush (&st, 20);
    if (error != 0) return error;
    printStack (&st);
    printf ("%d --- %d\n", st.Size, st.capocity);

    int x = 0;
    error = stackPop (&st, &x);
    if (error != 0) return error;
    printf ("%d\n", x);
    printStack (&st);
    printf ("%d --- %d\n", st.Size, st.capocity);

    stackDtor (&st);

    return SUCCESS;
}



int stackCtor (Stack* st)
{
    int error = stackOK (st);
    if (error != 0)
    {
        stackDump (error);
        return error;
    }

    st->capocity = START_STACK_SIZE;
    st->Size = 0;

    st->data = (int*) calloc (st->capocity, sizeof (int));
    if (st->data == NULL)
    {
        printf ("Can't alloc memory\n");
        return ALLOC_ERROR;
    }

    return SUCCESS;
}

int stackPush (Stack* st, int value)
{
    int error = stackOK (st);
    if (error != 0)
    {
        stackDump (error);
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

int stackPop (Stack* st, int* x)
{
    int error = stackOK (st);
    if (error != 0)
    {
        stackDump (error);
        return error;
    }

    if (st->Size == 0)
    {
        printf ("Stack underflow\n");
        return STACK_UNDERFLOW;
    }

    *x = --st->Size;

    if (st->Size <= st->capocity/COEFFICIENT)
    {
        reallocate (st, st->capocity/COEFFICIENT);
    }


    return SUCCESS;
}

int stackDtor (Stack* st)
{
    int error = stackOK (st);
    if (error != 0)
    {
        stackDump (error);
        return error;
    }

    free (st->data);
    st->Size = -1;

    return SUCCESS;
}

int printStack (Stack* st)
{
    int error = stackOK (st);
    if (error != 0)
    {
        stackDump (error);
        return error;
    }

    for (unsigned num = 0; num < st->Size; num++)
    {
        printf ("%d\n", *(st->data + num * sizeof (int)));
    }

    return 0;
}

int reallocate (Stack* st, size_t newSize)
{
    int error = stackOK (st);
    if (error != 0)
    {
        stackDump (error);
        return error;
    }

    st->capocity = newSize;
    st->data = (int*) realloc (st->data, st->capocity);
    if (st->data == NULL)
        {
            printf ("Can't realloc memory\n");
            return ALLOC_ERROR;
        }

    return SUCCESS;
}

int stackOK (const Stack* st)
{
    if (!st) return VOID_STACK;
    if (st->Size < 0) return STACK_UNDERFLOW;
    if (st->capocity < st->Size) return STACK_OVERFLOW;

    return 0;
}

void stackDump (int error)
{
    switch (error)
    {
        case STACK_UNDERFLOW:
            logInfo (stdout, __FILE__, __LINE__, "Stack Underflow\n");
            break;

        case STACK_OVERFLOW:
            logInfo (stdout, __FILE__, __LINE__, "Stack Overflow\n");
            break;

        case VOID_STACK:
            logInfo (stdout, __FILE__, __LINE__, "Stack if NULL\n");

    }
}

void logInfo (FILE* ptrfile, const char* file, int line, const char* errorCode)
{
    fprintf (ptrfile, "%s:%d %s\n", file, line, errorCode);
}





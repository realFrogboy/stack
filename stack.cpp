#include "stack.h"

int stackCtor (Stack* st)
{
    assert (st);

    st->capocity = START_STACK_SIZE;
    st->Size = 0;

    st->data = (int*) calloc (st->capocity + 1, sizeof (int));
    if (st->data == NULL) LOG_INFO(ALLOC_ERROR);

    ((int*) st)[-1] = CANARY;
    //((char*) st)[sizeof (st->data) + sizeof (st->capocity) + sizeof (st->Size)] = CANARY;

    memset (st->data, POISON, st->capocity);

    st->data[0] = CANARY;
    SET_CANARY;

    ASSERT_OK(st);

    return SUCCESS;
}


//-----------------------------------------------------------------------------


int stackPush (Stack* st, int value)
{
    ASSERT_OK(st);

    if (st->Size >= st->capocity)
        reallocate (st, st->capocity * COEFFICIENT);

    st->Size++;
    *(st->data + st->Size * sizeof (int)) = value;

    ASSERT_OK(st);

    return SUCCESS;
}


//-----------------------------------------------------------------------------


int stackPop (Stack* st, int* x)
{
    ASSERT_OK(st);

    *x = --st->Size;

    if (st->Size < st->capocity/COEFFICIENT)
        reallocate (st, st->capocity/COEFFICIENT);

    ASSERT_OK(st);

    return SUCCESS;
}


//-----------------------------------------------------------------------------


int stackDtor (Stack* st)
{
    //ASSERT_OK(st);

    free (st->data);
    st->Size = -1;

    return SUCCESS;
}


//-----------------------------------------------------------------------------


int printStack (Stack* st)
{
    ASSERT_OK(st);

    for (unsigned num = st->Size; num >= 1; num--)
    {
        printf ("%d\n", *(st->data + num * sizeof (int)));
    }

    ASSERT_OK(st);

    return 0;
}


//-----------------------------------------------------------------------------


int reallocate (Stack* st, size_t newSize)
{
    ASSERT_OK(st);

    st->capocity = newSize;
    st->data = (int*) realloc (st->data, st->capocity + 1);
    if (st->data == NULL) LOG_INFO(REALLOC_ERROR);
    
    memset ((st->data + (st->Size + 1) * sizeof (int)), POISON,  st->capocity - st->Size);

    SET_CANARY;

    ASSERT_OK(st);

    return SUCCESS;
}


//-----------------------------------------------------------------------------


void stackDump (int error)
{
    switch (error)
    {
        case STACK_UNDERFLOW:
            printf ("\t\tERROR CODE: Stack Underflow\n");
            break;

        case STACK_OVERFLOW:
            printf ("\t\tERROR CODE: Stack Overflow\n");
            break;

        case VOID_STACK:
            printf ("\t\tERROR CODE: Pointer on tack is NULL\n");
            break;
        
        case ALLOC_ERROR:
            printf ("\t\tERROR CODE: Can't alloc meemory\n");
            break;
        
        case REALLOC_ERROR:
            printf ("\t\tERROR CODE: Can't realloc meemory\n");
            break;
        
        case DATA_CANARY_LEFT_ERROR:
            printf ("\t\tERROR CODE: Data's left canary was changed\n");
            break;
        
        case DATA_CANARY_RIGHT_ERROR:
            printf ("\t\tERROR CODE: Data's right canary was changed\n");
            break;
        
        case STACK_CANARY_LEFT_ERROR:
            printf ("\t\tERROR CODE: Stack's left canary was changed\n");
            break;
        
        case STACK_CANARY_RIGHT_ERROR:
            printf ("\t\tERROR CODE: Stack's right canary was changed\n");
            break;

    }
}


//-----------------------------------------------------------------------------


void cleanBuffer ()
{
    while (getchar() != '\n') continue;
}



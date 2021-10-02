#include "stack.h"

int stackCtor (Stack* st)
{
    assert (st);

    st->capocity = START_STACK_SIZE;
    st->Size = 0;

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

    st->Size++;
    *(st->data + st->Size * sizeof (int)) = value;

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

    if (st->Size < st->capocity/COEFFICIENT)
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


int RunUnitTest ()
{
    int numOfSuccessful = 0;
    
    int numOfValues[NUM_OF_TESTS]                = {5, 6, 7, 8, 5, 5, 4, 3};
    int values[NUM_OF_TESTS][MAX_NUM_OF_VALUES]  = {{10, 20, 30, 40, 50},
                                                    {1, 2 , 3 , 4 , 5, 6},
                                                    {11, 12, 13, 14, 15, 16, 17},
                                                    {-1, -2, -3, -4, -5, -6, -7, -8},
                                                    {0, 0, 0, 0, 0},
                                                    {-11, -12, -13, -14, -15},
                                                    {5, 6, 7, 8},
                                                    {100, 200, 300}};

    int sumOfValues[NUM_OF_TESTS]                = {150, 21, 98, -36, 0, -65, 26, 600};
    int numOfDeleted[NUM_OF_TESTS]               = {1,   6,  3,  5,   2, 1,   0,  2};
    int sumAfterDelete[NUM_OF_TESTS]             = {100, 0,  50, -6,  0, -50, 26, 100};
    int numAfterDelete[NUM_OF_TESTS]             = {4,   0,  4,  3,   3, 4,   4,  1};

    for (int num = 0; num < NUM_OF_TESTS; num++)
    {
        if (!UnitTest (values, numOfValues[num], sumOfValues[num], numOfDeleted[num], sumAfterDelete[num], numAfterDelete[num])) 
            numOfSuccessful++;
    }

    return numOfSuccessful;
}


int UnitTest (int values[][MAX_NUM_OF_VALUES], int numOfValues, int sumOfValues, int numOfDeleted, int sumAfterDelete, int numAfterDelete)
{
    int error = 0;
    static int numTest = 0;

    struct Stack st ;
    error = stackCtor (&st);
    if (error != 0) return error;

    for (int num = 0; num < numOfValues; num++)
    {
        error = stackPush (&st, values[numTest][num]);
        if (error != 0) return error;
    }

    int summBeforeDelete = summ (&st);

    int remainingNum = numOfValues;

    for (int num = 0; num < numOfDeleted; num++)
    {
        error = stackPop (&st, &remainingNum);
        if (error != 0) return error;
    }

    int summAfterDelete = summ (&st);

    error = stackDtor (&st);
    if (error != 0) return error;

    if ((sumOfValues != summBeforeDelete)||(sumAfterDelete != summAfterDelete)||(numAfterDelete != remainingNum))
    {
        printf ("Test #%d --- ERROR\n"
                "Expexted values: sumOfValues = %3d, sumAfterDelete = %3d, numAfterDelete = %3d\n"
                "Results: ------------------- = %3d, -------------- = %3d, ---------------= %3d\n",
                (numTest+1), sumOfValues, sumAfterDelete, numAfterDelete, summBeforeDelete, summAfterDelete, remainingNum);
        
        numTest++;

        return FAIL;
    }

    numTest++;

    return SUCCESS;
}

int summ (const Stack* st)
{
    int res = 0;

    for (int num = 1; num <= st->Size; num++)
        res += *(st->data + num * sizeof(int));
    
    return res;
}


void cleanBuffer ()
{
    while (getchar() != '\n') continue;
}



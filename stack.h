#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#define LOG_INFO(errorCode) { \
    printf ("%s:%d, ERROR #%d\n.", __FILE__, __LINE__, errorCode); }

#define ASSERT_OK(st) { \
    if (!st) return VOID_STACK; \
    if (st->Size < 0) return STACK_UNDERFLOW; \
    if (st->capocity < st->Size) return STACK_OVERFLOW; }


enum ERRORS
{
    STACK_UNDERFLOW    = 10101,
    STACK_OVERFLOW     = 10201,
    ALLOC_ERROR        = 10301,
    REALLOC_ERROR      = 10401,
    VOID_STACK         = 10501,
    INCORRECT_INPUT    = 10601,
    MEMSET_ERROR       = 10701
};

enum RESULTS
{
    SUCCESS            = 0,
    FAIL               = 1 
};

const int START_STACK_SIZE = 2;
const int COEFFICIENT = 2;
const int NUM_OF_TESTS = 8;
const int MAX_NUM_OF_VALUES = 10;
const int POISON = -99;

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
void stackDump (const char* name, int line, int error);
void logInfo (FILE* ptrfile, const char* file, int line, const char* errorCode);
void cleanBuffer ();
int RunUnitTest ();
int summ (const Stack* st);
int UnitTest (int values[][MAX_NUM_OF_VALUES], int numOfValues, int sumOfValues, int numOfDeleted, 
              int sumAfterDelete, int numAfterDelete);


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
    VOID_STACK         = 10501,
    INCORRECT_INPUT    = 10601
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
void stackDump (const char* name, int line, int error);
void logInfo (FILE* ptrfile, const char* file, int line, const char* errorCode);
void cleanBuffer ();


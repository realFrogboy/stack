#ifndef STACK_H

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#define STACK_H


#ifndef LOG_INFO
#define LOG_INFO(errorCode) { \
    printf (" %s:%d, ERROR #%d:\n.", __FILE__, __LINE__, errorCode); \
    stackDump (errorCode); \
    return errorCode; }
#endif


#ifndef ASSERT_OK
#define ASSERT_OK(st) { \
    if (!st) return VOID_STACK; \
    if (st->Size < 0) return STACK_UNDERFLOW; \
    if (st->capocity < st->Size) return STACK_OVERFLOW; \
    if (st->data[0] != CANARY) return DATA_CANARY_LEFT_ERROR; \
    if (st->data[st->capocity + 1] != CANARY) return DATA_CANARY_RIGHT_ERROR; \
    if (((int*) st)[-1] != CANARY) return STACK_CANARY_LEFT_ERROR; \
    if (0) return STACK_CANARY_RIGHT_ERROR; }
#endif


#ifndef BAD_INPUT
#define BAD_INPUT  printf ("Incorrect input!\nPlease, enter a number.\n")
#endif


#ifndef PRINT_STACK
#define PRINT_STACK(st) { \
    printStack (&st); \
    printf ("%ld --- %ld\n", st.Size, st.capocity); }
#endif


#ifndef SET_CANARY 
#define SET_CANARY st->data[st->capocity + 1] = CANARY
#endif

#ifndef GET_VALUE
#define GET_VALUE(text, val) { \
    printf (text); \
        while ((scanf ("%d", &val)) != 1) \
        { \
            printf ("Incorrect input!\nPlease, enter a number.\n"); \
            cleanBuffer (); \
        } \
    }
#endif

#ifndef ERROR_MESSAGE
#define ERROR_MESSAGE(text) { \
    printf ("Incorrect input!\n" \
                text); \
        cleanBuffer (); \
    }
#endif

enum ERRORS
{
    STACK_UNDERFLOW          = 10101,
    STACK_OVERFLOW           = 10201,
    ALLOC_ERROR              = 10301,
    REALLOC_ERROR            = 10401,
    VOID_STACK               = 10501,
    DATA_CANARY_LEFT_ERROR   = 10601,
    DATA_CANARY_RIGHT_ERROR  = 10701,
    STACK_CANARY_LEFT_ERROR  = 10801,
    STACK_CANARY_RIGHT_ERROR = 10901
};



enum RESULTS
{
    SUCCESS = 0,
    FAIL    = 1 
};


//typedef long canary_t;


const int CANARY            = 0xBADCAFE; 
const int START_STACK_SIZE  = 2;
const int COEFFICIENT       = 2;
const int NUM_OF_TESTS      = 8;
const int MAX_NUM_OF_VALUES = 10;
const int POISON            = -99;



struct Stack
{
    int* data;
    size_t capocity;
    size_t Size;
};


int stackCtor (Stack* st);
int stackPush (Stack* st, int value);
int stackPop (Stack* st, int* x);
int stackDtor (Stack* st);
int printStack(Stack* st);
int reallocate (Stack* st, size_t newSize);
void stackDump (int error);
void cleanBuffer ();
int RunUnitTest ();
int summ (const Stack* st);
int UnitTest (int values[][MAX_NUM_OF_VALUES], int numOfValues, int sumOfValues, int numOfDeleted, 
              int sumAfterDelete, int numAfterDelete);

#endif

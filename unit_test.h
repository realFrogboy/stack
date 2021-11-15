#include "stack.h"

enum RESULTS
{
    SUCCESS = 0,
    FAIL    = 1 
};

const int NUM_OF_TESTS = 8;
const int MAX_NUM_OF_VALUES = 10;

int RunUnitTest ();
int summ (const Stack* st);
int UnitTest (int values[][MAX_NUM_OF_VALUES], int numOfValues, int sumOfValues, int numOfDeleted, 
              int sumAfterDelete, int numAfterDelete);
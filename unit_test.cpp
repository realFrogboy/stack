#include "stack.h"

int RunUnitTest ()
{
    int numOfSuccessful = 0;
    
    int values[NUM_OF_TESTS][MAX_NUM_OF_VALUES]  = {{10, 20, 30, 40, 50},
                                                    {1, 2 , 3 , 4 , 5, 6},
                                                    {11, 12, 13, 14, 15, 16, 17},
                                                    {-1, -2, -3, -4, -5, -6, -7, -8},
                                                    {0, 0, 0, 0, 0},
                                                    {-11, -12, -13, -14, -15},
                                                    {5, 6, 7, 8},
                                                    {100, 200, 300}};

    int numOfValues[NUM_OF_TESTS]                = {5,   6,  7,  8,   5, 5,   4,  3};
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


//-----------------------------------------------------------------------------


int UnitTest (int values[][MAX_NUM_OF_VALUES], int numOfValues, int sumOfValues, int numOfDeleted, int sumAfterDelete, int numAfterDelete)
{
    int error = 0;
    static int numTest = 0;

    struct Stack st ;
    if ((error = stackCtor (&st)) != 0) LOG_INFO(error);

    for (int num = 0; num < numOfValues; num++)
        if ((error = stackPush (&st, values[numTest][num])) != 0) LOG_INFO(error);

    int summBeforeDelete = summ (&st);

    int remainingNum = numOfValues;

    for (int num = 0; num < numOfDeleted; num++)
    {
        if ((error = stackPop (&st, &remainingNum)) != 0) LOG_INFO(error);
    }

    //if (((int*) &st)[-1] != CANARY) printf ("hsfvbdh\n");

    int summAfterDelete = summ (&st);

    //if (((int*) &st)[-1] != CANARY) printf ("hsfvbdh\n");

    if ((error = stackDtor (&st)) != 0) LOG_INFO(error);

    if ((sumOfValues != summBeforeDelete) || (sumAfterDelete != summAfterDelete) || (numAfterDelete != remainingNum))
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


//-----------------------------------------------------------------------------


int summ (const Stack* st)
{   
    //ASSERT_OK(st);

    int res = 0;

    for (int num = 1; num <= st->Size; num++)
        res += *(st->data + num * sizeof(int));

    //ASSERT_OK(st);
    
    return res;
}
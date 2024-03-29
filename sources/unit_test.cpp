#include "stack.h"

const int MAX_NUM_OF_VALUES  = 10;
const int NUM_OF_TESTS = 8;
const int TEST_FAILD = 1;
//int DEBUG_LEVEL = 3;

int RunUnitTest ();
int summ (const Stack* st);
int UnitTest (int values[][MAX_NUM_OF_VALUES], int numOfValues, int sumOfValues, int numOfDeleted, 
              int sumAfterDelete, int numAfterDelete);

/*int main() {
    int numOfSuccess = RunUnitTest ();
    printf ("Number of successful tests: %d.\n", numOfSuccess);

    return 0;
}*/

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
    static int numTest = 0;

    struct Stack st;
    stackCtor (&st);

    for (int num = 0; num < numOfValues; num++)
        stackPush (&st, values[numTest][num]);

    int summBeforeDelete = summ (&st);
    

    for (int num = 0; num < numOfDeleted; num++)
    {
        stackPop (&st);
    }

    long remainingNum = st.Size;


    int summAfterDelete = summ (&st);


    stackDtor (&st);

    if ((sumOfValues != summBeforeDelete) || (sumAfterDelete != summAfterDelete) || (numAfterDelete != remainingNum))
    {
        printf ("Test #%d --- ERROR\n"
                "Expected values: sumOfValues = %3d, sumAfterDelete = %3d, numAfterDelete = %3d\n"
                "Results: ------------------- = %3d, -------------- = %3d, ---------------= %3ld\n",
                (numTest+1), sumOfValues, sumAfterDelete, numAfterDelete, summBeforeDelete, summAfterDelete, remainingNum);
        
        numTest++;

        return TEST_FAILD ;
    }

    numTest++;

    return NO_ERRORS;
}


//-----------------------------------------------------------------------------


int summ (const Stack* st)
{   

    int res = 0;

    for (unsigned num = 0; num < st->Size; num++)
        res += *(st->data + num);

    
    return res;
}
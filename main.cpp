#include "stack.h"


int main (int argc, char** argv)
{
    int mode = 0;
    
    printf ("Run Tests? Press 0 or 1.\n");
    while (((scanf ("%d", &mode)) != 1) || (mode < 0) || (mode > 1)) 
        ERROR_MESSAGE("Please, enter 0 or 1.\n");

    if (mode)
    {
        int numOfSuccess = RunUnitTest ();
        printf ("Number of successful tests: %d / %d\n", numOfSuccess, NUM_OF_TESTS);

        return SUCCESS;
    }

    int error = 0, numOfNumbers = 0;

    printf ("Enter number of numbers\n");
    while (((scanf ("%d", &numOfNumbers)) != 1) || (numOfNumbers < 0))
        ERROR_MESSAGE("Number of numbers should be a number greater then 0.\n");


    struct Stack st;
    if ((error = stackCtor (&st)) != 0) LOG_INFO(error);
    PRINT_STACK(st);
    
    for (int num = 0; num < numOfNumbers; num++)
    {
        int val = 0;

        GET_VALUE("Enter value.\n", val);

        if ((error = stackPush (&st, val)) != 0) LOG_INFO(error);
        PRINT_STACK(st);
    }

    int numForDelet = 0, remainingNum = numOfNumbers;

    GET_VALUE("Enter number of delete.\n", numForDelet);

    int num = 0;
    while (num < numForDelet)
    {
        if ((error = stackPop (&st, &remainingNum)) != 0) LOG_INFO(error);
        num++;

        PRINT_STACK(st);
    }

    if ((error = stackDtor (&st)) != 0) LOG_INFO(error);
    PRINT_STACK(st);

    return SUCCESS;
}

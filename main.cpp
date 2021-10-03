#include "stack.h"

int main (int argc, char** argv)
{
    int mode = 0;
    
    printf ("Run Tests? Press 0 or 1.\n");
    while (((scanf ("%d", &mode)) != 1) || (mode < 0) || (mode > 1))
    {
        printf ("Incorrect input!\n"
                "Please, enter 0 or 1.\n");
        cleanBuffer ();
    }

    if (mode)
    {
        int numOfSuccess = RunUnitTest ();
        printf ("Number of successful tests: %d / %d\n", numOfSuccess, NUM_OF_TESTS);
        return SUCCESS;
    }

    int error = 0, numOfNumbers = 0;

    printf ("Enter number of numbers\n");
    while (((scanf ("%d", &numOfNumbers)) != 1) || (numOfNumbers < 0))
    {
        printf ("Incorrect input!\n"
                "Number of numbers should be a number greater then 0.\n");
        cleanBuffer ();
    }


    struct Stack st;
    if ((error = stackCtor (&st)) != 0) LOG_INFO(error);
    PRINT_STACK(st);
    
    for (int num = 0; num < numOfNumbers; num++)
    {
        int val = 0;

        printf ("Enter value.\n");
        while ((scanf ("%d", &val)) != 1)
        {
            BAD_INPUT;
            cleanBuffer ();
        }

        if ((error = stackPush (&st, val)) != 0) LOG_INFO(error);
        PRINT_STACK(st);
    }

    int numDel = 0, remainingNum = numOfNumbers;

    printf ("Enter number of delete.\n");
    while ((scanf ("%d", &numDel)) != 1)
    {
        BAD_INPUT;
        cleanBuffer ();
    }


    int num = 0;
    while (num < numDel)
    {
        if ((error = stackPop (&st, &remainingNum)) != 0) LOG_INFO(error);
        num++;

        PRINT_STACK(st);
    }

    if ((error = stackDtor (&st)) != 0) LOG_INFO(error);
    PRINT_STACK(st);

    return SUCCESS;
}

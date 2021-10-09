#include "stack.h"

int DEBUG_LEVEL = 0;

int main (int argc, char** argv)
{
    int mode = 0;

    printf ("Choose DEBUG LEVEL:\n"
            "LEVEL 0 --- No security\n"
            "\n"
            "LEVEL 1 --- Void ptr security\n"
            "            Stack Overflow security\n"
            "            Stack Underflow security\n"
            "\n"
            "LEVEL 2 --- Void ptr security\n"
            "            Stack Overflow security\n"
            "            Stack Underflow security\n"
            "            Stack canary security\n"
            "\n"
            "LEVEL 3 --- Void ptr security\n"
            "            Stack Overflow security\n"
            "            Stack Underflow security\n"
            "            Stack canary security\n"
            "            Stack hash security\n");
    
    while (((scanf ("%d", &DEBUG_LEVEL)) != 1) || (DEBUG_LEVEL < 0) || (DEBUG_LEVEL > 3)) 
     { 
        printf ("Incorrect input!\n" 
               "Please, enter 0, 1, 2 or 3.\n"); 
        cleanBuffer (); 
    }
    
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

        return NO_ERRORS;
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
    printStack(&st);
    
    for (int num = 0; num < numOfNumbers; num++)
    {
        int val = 0;

        getValue ("Enter a value\n", &val);

        if ((error = stackPush (&st, val)) != 0) LOG_INFO(error);
        printStack(&st);
    }

    int numForDelet = 0, remainingNum = numOfNumbers;

    getValue ("Enter number of delete.\n", &numForDelet);

    int num = 0;
    while (num < numForDelet)
    {
        if ((error = stackPop (&st)) != 0) LOG_INFO(error);
        num++;

        printStack(&st);
    }

    if ((error = stackDtor (&st)) != 0) LOG_INFO(error);

    return NO_ERRORS;
}

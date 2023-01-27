#include "stack.h"

void getValue (const char *str, int *val);
int RunUnitTest ();
void cleanBuffer ();

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
        printf ("Number of successful tests: %d.\n", numOfSuccess);

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
    if ((error = stackCtor (&st)) != 0)
        printStack(&st);
    
    for (int num = 0; num < numOfNumbers; num++)
    {
        int val = 0;

        getValue ("Enter a value\n", &val);

        if ((error = stackPush (&st, val)) != 0)
            printStack(&st);
    }

    int numForDelet = 0, remainingNum = numOfNumbers;

    getValue ("Enter number of delete.\n", &numForDelet);

    int num = 0;
    while (num < numForDelet)
    {
        if ((error = stackPop (&st)) != 0)
            printStack(&st);
        num++;
    }

    error = stackDtor(&st);

    return NO_ERRORS;
}


//-----------------------------------------------------------------------------


void getValue (const char *str, int *val)
{
    printf ("%s\n", str); 
    while ((scanf ("%d", val)) != 1) 
    { 
        printf ("Incorrect input!\nPlease, enter a number.\n"); 
        cleanBuffer (); 
    } 
}


//-----------------------------------------------------------------------------


void cleanBuffer ()
{
    while (getchar() != '\n') continue;
}
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

    int error = 0, numT = 0;

    printf ("Enter number of numbers\n");
    while (((scanf ("%d", &numT)) != 1) || (numT < 0))
    {
        printf ("Incorrect input!\n"
                "Number of numbers should be a number greater then 0.\n");
        cleanBuffer ();
    }


    struct Stack st ;
    error = stackCtor (&st);
    if (error != 0) return error;

    printStack (&st);
    printf ("%ld --- %ld\n", st.Size, st.capocity);

    for (int num = 0; num < numT; num++)
    {
        int val = 0;

        printf ("Enter value.\n");
        while ((scanf ("%d", &val)) != 1)
        {
            printf ("Incorrect input!\n"
                    "Please, enter a number.\n");
            cleanBuffer ();
        }


        error = stackPush (&st, val);
        if (error != 0) return error;

        printStack (&st);
        printf ("%ld --- %ld\n", st.Size, st.capocity);
    }

    int numDel = 0, remainingNum = 0;

    printf ("Enter number of delete.\n");
    while ((scanf ("%d", &numDel)) != 1)
    {
        printf ("Incorrect input!\n"
                "Please, enter a number.\n");
        cleanBuffer ();
    }


    int num = 0;
    while (num < numDel)
    {
        error = stackPop (&st, &remainingNum);
        if (error != 0) return error;
        num++;

        printStack (&st);
        printf ("%ld --- %ld\n", st.Size, st.capocity);
    }


    error = stackDtor (&st);
    if (error != 0) return error;

    printStack (&st);
    printf ("%ld --- %ld\n", st.Size, st.capocity);

    return SUCCESS;
}

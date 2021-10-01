#include "stack.h"

int main ()
{
    int error = 0, numT = 0;

    printf ("Enter number of numbers\n");
    if ((scanf ("%d", &numT)) != 1)
    {
        printf ("Incorrect input.\n");
        return INCORRECT_INPUT;
    }

    cleanBuffer();


    struct Stack st ;
    error = stackCtor (&st);
    if (error != 0) return error;

    printStack (&st);
    printf ("%ld --- %ld\n", st.Size, st.capocity);

    for (int num = 1; num < numT; num++)
    {
        int val = 0;

        printf ("Enter value.\n");
        if ((scanf ("%d", &val)) != 1)
        {
            printf ("Incorrect input.\n");
            return INCORRECT_INPUT;
        }


        error = stackPush (&st, val);
        if (error != 0) return error;

        printStack (&st);
        printf ("%ld --- %ld\n", st.Size, st.capocity);
    }

    int numDel = 0, remainingNum = 0;

    printf ("Enter number of delete.\n");
    if ((scanf ("%d", &numDel)) != 1)
    {
        printf ("Incorrect input.\n");
        return INCORRECT_INPUT;
    }

    printf ("\n\n%d\n\n\n", numDel);


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

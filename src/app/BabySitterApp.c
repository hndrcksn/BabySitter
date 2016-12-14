#include <stdio.h>
#include <stdlib.h>
#include "BabySitterApp.h"
#include "../lib/BabySitterCalc.h"

char *getInput(void)
{
    char *input = malloc(100);
    if (input == NULL)
    {
        return NULL;
    }

    char *linePtr = input;
    size_t lenmax = 100, len = lenmax;
    int c;

    for (;;)
    {
        c = fgetc(stdin);
        if(c == EOF)
        {
            break;
        }

        if(--len == 0)
        {
            len = lenmax;
            char *linen = realloc(linePtr, lenmax *= 2);

            if(linen == NULL)
            {
                free(linePtr);
                return NULL;
            }
            input = linen + (input - linePtr);
            linePtr = linen;
        }

        if((*input++ = c) == '\n')
        {
            break;
        }
    }
    *input = '\0';
    return linePtr;
}

const char greeting[] = "Welcome to the BabySitterApp. Type 'q' to exit or 'r' to reset to the beginning.\n"
                        "Enter a time string (like 5:00PM) for validation.\n"
                        "Input>";

int main(void)
{
    char *newValue, *posn;

    GREETING: printf("%s\n", greeting);

    newValue = getInput();
    if ((posn=strchr(newValue, '\n')) != NULL)
    {
        *posn = '\0';
    }

    if (strncmp(newValue, "q", strlen(newValue)) == 0)
    {
        return 0;
    }
    else if (strncmp(newValue, "r", strlen(newValue)) == 0)
    {
        goto GREETING;
    }

    if (isValidTimeString(newValue))
    {
        printf("%s is valid!\n", newValue);
        if (isInBounds(newValue))
        {
            printf("%s is in bounds!\n", newValue);
        }
        else
        {
            printf("%s is out of bounds!\n", newValue);
        }
    }
    else
    {
        printf("%s is not valid, len = %ld\n", newValue, strlen(newValue));
    }

    goto GREETING;

    return 0;
}


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

e_state_type handleInput(char *outStr, e_state_type currState)
{
    char *newValue, *posn;
    e_state_type newState = currState;

    newValue = getInput();
    if ((posn=strchr(newValue, '\n')) != NULL)
    {
        *posn = '\0';
    }

    if (strncmp(newValue, "q", strlen(newValue)) == 0)
    {
        newState = E_GOODBYE;
    }
    else if (strncmp(newValue, "r", strlen(newValue)) == 0)
    {
        newState = E_GREET_INPUT_START;
    }
    else if (outStr != NULL)
    {
        if (isValidTimeString(newValue) && isInBounds(newValue))
        {
            strncpy(outStr, newValue, strlen(newValue));
            newState = currState + 1;
        }
        else if (!isValidTimeString(newValue))
        {
            printf("\nOOPS! %s is not a valid time string. Please try again\n", newValue);
        }
        else if (!isInBounds(newValue))
        {
            printf("\nOOPS! Input value (%s) must be between 5:00PM and 4:00AM. Please try again\n", newValue);
        }
    }

    return newState;
}

const char greeting[] = "Welcome to the BabySitterApp. Type 'q' or ENTER on an empty line to exit or 'r' to reset to the beginning.\n"
                        "Enter the babysitting start time (between 5:00PM and 4:00AM) to begin...";

const char inputEndMsg[] = "Please enter the end time...";

const char inputBedMsg[] = "Please enter the bedtime...";

const char outputEarningsMsg[] = "Your earnings are as follows...";

const char goodByeMsg[] = "BabySitterApp is now exiting...";

int main(void)
{
    e_state_type myState = E_GREET_INPUT_START;

    char inStartTimeStr[32];
    inStartTimeStr[0] = '\0';
    char inEndTimeStr[32];
    inEndTimeStr[0] = '\0';
    char inBedTimeStr[32];
    inBedTimeStr[0] = '\0';
    int outEarnings = 0;

    while (true)
    {
        switch (myState) {
            case E_GREET_INPUT_START:
                inStartTimeStr[0] = '\0';
                inEndTimeStr[0] = '\0';
                inBedTimeStr[0] = '\0';
                outEarnings = 0;

                printf("%s\n", greeting);
                myState = handleInput(inStartTimeStr, myState);
                break;

            case E_INPUT_END:
                printf("%s\n", inputEndMsg);
                myState = handleInput(inEndTimeStr, myState);
                break;

            case E_INPUT_BED:
                printf("%s\n", inputBedMsg);
                myState = handleInput(inBedTimeStr, myState);
                break;

            case E_OUTPUT_EARNINGS_WAIT:
                printf("%s\n", outputEarningsMsg);
                outEarnings = getTotalFundsDue(inStartTimeStr, inEndTimeStr, inBedTimeStr);
                printf("$%d\n", outEarnings);
                myState = handleInput(NULL, myState);
                break;

            case E_GOODBYE:
                printf("%s\n", goodByeMsg);
                return 0;
                break;

            default:
                break;
        }
    }

    return 0;
}


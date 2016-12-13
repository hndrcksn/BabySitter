#include <stdlib.h>
#include <string.h>
#include "BabySitterCalc.h"

// Shift time boundaries
const char MINSTARTTIME[] = "5:00PM";
const char MAXENDTIME[] = "4:00AM";

bool isEarliestStartTime(const char *inTimeStr)
{
    if (strcmp(MINSTARTTIME, inTimeStr) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isLatestEndTime(const char *inTimeStr)
{
    if (strcmp(MAXENDTIME, inTimeStr) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}


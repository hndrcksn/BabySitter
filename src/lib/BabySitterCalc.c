#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
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

// String & time conversion functions
time_t strToTime(const char *inString)
{
    char timeBuffer[32];
    sprintf(timeBuffer, "%s %s", "1970-01-01 ", inString);
    struct tm start_epoch = {0};
    strptime(timeBuffer, "%Y-%m-%d %-I:%M%p", &start_epoch);
    time_t rawTime = timegm(&start_epoch);

    return rawTime;
}

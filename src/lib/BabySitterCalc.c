#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include "BabySitterCalc.h"

// Shift time boundaries
const char MINSTARTTIME[] = "5:00PM";
const char MAXENDTIME[] = "4:00AM";
const time_t MINSTARTTIME_T = 61200;
const time_t MAXENDTIME_T = 100800;

// Remuneration rates
const int MID_RATE = 8;

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

    // Hours after midnight (00:00AM) fall on the next day
    char date[12];
    if (strstr(inString, "PM") != NULL)
    {
        strncpy(date, "1970-01-01 ", sizeof(date));
    }
    else
    {
        strncpy(date, "1970-01-02 ", sizeof(date));
    }

    sprintf(timeBuffer, "%s %s", date, inString);
    struct tm start_epoch = {0};
    strptime(timeBuffer, "%Y-%m-%d %-I:%M%p", &start_epoch);
    time_t rawTime = timegm(&start_epoch);

    return rawTime;
}

char *timeToStr(time_t inTime, char *inBuffer, int inSize)
{
    strftime(inBuffer, inSize, "%-I:%M%p", gmtime(&inTime));
    return inBuffer;
}

bool isInBounds(const char *inTimeStr)
{
    time_t inTime = strToTime(inTimeStr);

    if (inTime >= MINSTARTTIME_T && inTime <= MAXENDTIME_T)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*
 * Validates a time string by converting it into a struct tm and then extracts an output
 * time string. If the two strings are identical then the input string is valid.
 */
bool isValidTimeString(const char *inString)
{
    char timeBuffer[32];
    char date[12];
    char outTime[8];

    // Create time/date string from input string. Relative to start of Unix epoch
    strncpy(date, "1970-01-01 ", sizeof(date));
    sprintf(timeBuffer, "%s %s", date, inString);

    // Initialize and set struct tm object to date and input time
    struct tm start_epoch = {0};
    strptime(timeBuffer, "%Y-%m-%d %-I:%M%p", &start_epoch);

    // Retrieve time in expected format from struct tm object
    strftime(outTime, sizeof(outTime), "%-I:%M%p", &start_epoch);

    // Compare output string with input string. If it is different then input string wasn't valid
    if (strcmp(inString, outTime) == 0)
    {
        return true;
    }
    else
    {
        // Retrieve time in alternate format from struct tm object
        strftime(outTime, sizeof(outTime), "%I:%M%p", &start_epoch);

        if (strcmp(inString, outTime) == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

// Remuneration functions
int getMidRateDues(int hours)
{
    if (hours <= 0)
    {
        return 0;
    }
    else
    {
        return hours * MID_RATE;
    }
}


#ifndef BABYSITTERCALC_H
#define BABYSITTERCALC_H

#include <stdbool.h>

// String functions
bool isEarliestStartTime(const char *inTimeStr);
bool isLatestEndTime(const char *inTimeStr);

// String & time conversion functions
time_t strToTime(const char *inString);
char *timeToStr(time_t inTime, char *inBuffer, int inSize);

// Time string validation
bool isInBounds(const char *inTimeStr);
bool isValidTimeString(const char *inString);

// Remuneration functions
int getMidRateDues(int hours);

#endif /* BABYSITTERCALC_H */


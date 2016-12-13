#include <stdio.h>
#include "BabySitterApp.h"
#include "../lib/BabySitterCalc.h"

const char greeting[] = "Welcome to the BabySitterApp. Type 'q' or 'Ctrl-D' to exit.";

int main(void)
{
    printf("%s\n", greeting);
    const char dateTime[] = "5:00PM";
    if (isValidTimeString(dateTime))
    {
        printf("%s is valid!\n", dateTime);
        if (isInBounds(dateTime))
        {
            printf("%s is in bounds!\n", dateTime);
        }
    }

    return 0;
}


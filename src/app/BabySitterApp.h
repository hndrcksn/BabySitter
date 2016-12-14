#ifndef BABYSITTERAPP_H
#define BABYSITTERAPP_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef enum {E_GREET_INPUT_START = 0, E_INPUT_END, E_INPUT_BED, E_OUTPUT_EARNINGS_WAIT, E_GOODBYE } e_state_type;

char *getInput(void);

#endif /* BABYSITTERAPP_H */


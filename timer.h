#include "time.h"


time_t start;
time_t end;
time_t elapsed;

/* Returns time(NULL) */
time_t timer_start();

/* Returns 1 if timer has passed t seconds */
int timer_is_time_out(time_t start,int t);


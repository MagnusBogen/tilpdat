#include "time.h"


time_t start;
time_t end;
time_t elapsed;
time_t timer_start();
int timer_is_time_out(time_t start,int t);
int timer_delay(int t);
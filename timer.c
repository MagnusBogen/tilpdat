#include <stdio.h>
#include "timer.h"
#include "time.h"
 
time_t timer_start() {
    time_t start = time(NULL);
    return start;
}
 
int timer_is_time_out(time_t start,int t) {
    time_t end = time(NULL);
    time_t elapsed = end - start;
 
    if (elapsed >= t){
    return 1;
    }
    return 0;
}
 


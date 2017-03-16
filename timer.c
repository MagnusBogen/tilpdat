#include <stdio.h>
#include "timer.h"
#include "time.h"
#include "register.h"   
#include "elev.h"
 
 
 
time_t timer_start() {
    time_t start = time(NULL);
    printf("start %ld\n", start);
    return start;
}
 
int timer_is_time_out(time_t start,int t) {
    time_t end = time(NULL);
    time_t elapsed = end - start;
 
    if (elapsed >= t){
    printf("Time is out\n");
    return 1;
    }
    return 0;
}
 
 
int timer_delay(int t){
 
    time_t start = timer_start();
    while(1){
        register_update();
        if(buttonRegister[0][elev_get_floor_sensor_signal()] || buttonRegister[1][elev_get_floor_sensor_signal()] || buttonRegister[2][elev_get_floor_sensor_signal()]){
            register_reset_floor(elev_get_floor_sensor_signal());
            start = timer_start();
            
        }
        if(elev_get_stop_signal()){
            return(0);
        }
         
        else if(timer_is_time_out(start,t)){
            return 1;
        }
    }
return 0;
}

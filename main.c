#include "elev.h"
#include "FSM.h"

#include <stdio.h>


int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }
    elev_set_motor_direction(DIRN_STOP);
    
    
    int running = 1;
    ElevatorState currentState = INIT;
    while(running){
	switch(currentState){
	    case INIT:
	        currentState = init();
	        break;
	    case IDLE:
		  currentState = idleElevator();
		  break;
        case UP:
            break;
        case DOWN:
		  break;
	}
    }
    
    return 0;
}

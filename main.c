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
    elev_set_motor_direction(DIRN_DOWN);
    

    ElevatorState currentState = INIT;
    while(1){
	switch(currentState){
	    case INIT:
	        currentState = do_INIT();
	        break;
	    case IDLE:
		  currentState = do_IDLE();
		  break;
        case UP:
        	currentState = do_UP();
            break;
        case DOWN:
        	currentState = do_DOWN();
		  break;
		case FLOOR:
			currentState = do_FLOOR();
			break;

		case STOP:
			currentState = do_STOP();
			break;
	}
    }
    
    return 0;
  
}

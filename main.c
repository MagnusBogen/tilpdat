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
    

    ElevatorState currentState = do_INIT();
    while(1){
	switch(currentState){
	    case INIT:
	        currentState = do_INIT();
	        break;
	    case IDLE:
		  currentState = do_IDLE();
		  break;
        case UP:
            break;
        case DOWN:
		  break;
		case FLOOR:
			break;

		case STOP:
			break;
	}
    }
    
    return 0;
}

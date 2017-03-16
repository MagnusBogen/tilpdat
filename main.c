#include "elev.h"
#include "FSM.h"
#include <stdio.h>


int main() {
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }
    
    ElevatorState currentState = INIT;
    while(1){
	switch(currentState){
	    case INIT:
	        currentState = fsm_do_INIT();
	        break;
	    case IDLE:
		  currentState = fsm_do_IDLE();
		  break;
        case UP:
        	currentState = fsm_do_UP();
            break;
        case DOWN:
        	currentState = fsm_do_DOWN();
		  break;
		case FLOOR:
			currentState = fsm_do_FLOOR();
			break;

		case STOP:
			currentState = fsm_do_STOP();
			break;
	}
    }
    
    return 0;
    
  
}

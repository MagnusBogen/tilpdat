#include <time.h>
#include "timer.h"
#include <stdio.h>
#include "elev.h"
#include "register.h"

/*	Elevator state for functions in fsm */
typedef enum ElevatorState{INIT, IDLE, UP, DOWN, FLOOR,STOP}ElevatorState;

int lastDir;
int lastFloor;


/*	Execute function for the INIT state. 
	Returns the next ElevatorState   	
	Poosible returns: INIT, IDLE                  */
ElevatorState fsm_do_INIT();


/*	Execute function for the IDLE state. 
	Returns the next ElevatorState   	
	Poosible returns: DOWN, UP, FLOOR, IDLE, STOP  */
ElevatorState fsm_do_IDLE();


/*	Execute function for the UP state. 
	Returns the next ElevatorState
	Poosible returns: UP, FLOOR, STOP              */
ElevatorState fsm_do_UP();


/*	Execute function for the DOWN state. 
	Returns the next ElevatorState   	
	Poosible returns: DOWN, FLOOR, STOP            */
ElevatorState fsm_do_DOWN();


/*	Execute function for the FLOOR state. 
	Returns the next ElevatorState   	
	Poosible returns: IDLE, STOP                   */
ElevatorState fsm_do_FLOOR();


/*	Execute function for the STOP state. 
	Returns the next ElevatorState   	
	Poosible returns: DOWN, UP, FLOOR, INIT        */
ElevatorState fsm_do_STOP();
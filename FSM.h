#include <time.h>
#include <stdio.h>
#include "elev.h"
#include "register.h"


typedef enum ElevatorState{INIT, IDLE, UP, DOWN, FLOOR,STOP}ElevatorState;

int lastDir;
int lastFloor;


ElevatorState fsm_do_INIT();


ElevatorState fsm_do_IDLE();


ElevatorState fsm_do_UP();


ElevatorState fsm_do_DOWN();


ElevatorState fsm_do_FLOOR();


ElevatorState fsm_do_STOP();



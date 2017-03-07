#include <time.h>
#include <stdio.h>
#include "elev.h"
#include "register.h"


typedef enum ElevatorState{INIT, IDLE, UP, DOWN, FLOOR,STOP}ElevatorState;

int dir;
int FSM_floor;


ElevatorState do_INIT();
ElevatorState do_IDLE();
ElevatorState do_UP();
ElevatorState do_DOWN();
ElevatorState do_FLOOR();
ElevatorState do_STOP();
ElevatorState test_dir();


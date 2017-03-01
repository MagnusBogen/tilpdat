#include <time.h>
#include <stdio.h>
#include "elev.h"
typedef enum ElevatorState{INIT, IDLE, UP, DOWN, FLOOR,STOP}ElevatorState;

ElevatorState do_INIT();
ElevatorState do_IDLE();
ElevatorState do_UP();
ElevatorState do_DOWN();
ElevatorState do_FLOOR();
ElevatorState do_STOP();

int next_dir(lastDir int, lastFloor int){

}

#include <time.h>
#include "elev.h"
typedef enum ElevatorState{INIT, IDLE, UP, DOWN, STOP}ElevatorState;

ElevatorState init();
ElevatorState idleElevator();

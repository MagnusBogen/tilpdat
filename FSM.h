#include <time.h>
#include "elev.h"
typedef enum ElevatorState{INIT, IDLE, UP, DOWN, FLOOR,STOP}ElevatorState;

ElevatorState init();
ElevatorState doIDLE();
ElevatorState doUP();
ElevatorState doDOWN();
ElevatorState doFLOOR();
ElevatorState doSTOP();

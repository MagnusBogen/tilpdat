#include "FSM.h"
#include <stdio.h>

ElevatorState do_INIT(){
	printf("In INIT\n");
	if(elev_get_floor_sensor_signal() == -1){

		elev_set_motor_direction(DIRN_DOWN);
		return INIT;
		

	}else{

		elev_set_motor_direction(DIRN_STOP);
		elev_set_floor_indicator(elev_get_floor_sensor_signal());
		return IDLE;
	}

}


ElevatorState do_IDLE(){
	printf("In IDLE\n");
	return IDLE;
}

ElevatorState do_UP(){
	printf("In UP\n");
	return IDLE;
}

ElevatorState do_DOWN(){
	printf("In DOWN\n");
	return IDLE;
}

ElevatorState do_FLOOR(){
	printf("In FLOOR\n");
	return IDLE;
}

ElevatorState do_STOP(){
	printf("In STOP\n");
	return IDLE;
}


#include "FSM.h"
#include "timer.h"
#include <stdio.h>


ElevatorState fsm_do_INIT(){
	register_reset_all();
	if(elev_get_floor_sensor_signal() == -1){
		elev_set_motor_direction(DIRN_DOWN);
		return INIT;
		

	}else{
		elev_set_motor_direction(DIRN_STOP);
		if (elev_get_floor_sensor_signal() >= 0){
		 elev_set_floor_indicator(elev_get_floor_sensor_signal());
		}
		lastDir = DIRN_DOWN;
		return IDLE;
	}
}


ElevatorState fsm_do_IDLE(){
	register_update();
	if (elev_get_stop_signal()){
		return STOP;
	}
	lastFloor = elev_get_floor_sensor_signal();
	switch (determ_dir(lastDir, lastFloor, IDLE)){
		case 1:
		return UP;
		break;

		case -1:
		return DOWN;
		break;

		case 0:
		return FLOOR;
		break;

		default:
		return IDLE;

	}
}

ElevatorState fsm_do_UP(){
	elev_set_motor_direction(DIRN_UP);
	lastDir = DIRN_UP;
	register_update();
	if (elev_get_stop_signal()){
		return STOP;
	}
	lastFloor = elev_get_floor_sensor_signal();
	if (elev_get_floor_sensor_signal()!= -1){
		switch (determ_dir(DIRN_UP, lastFloor, UP)){
			case 0:
			return FLOOR;
			break;

			default:
			return UP;
			break;
		}
	}
}

ElevatorState fsm_do_DOWN(){
	lastDir = DIRN_DOWN;
	elev_set_motor_direction(DIRN_DOWN);
	register_update();
	if (elev_get_stop_signal()){
		return STOP;
	}
	lastFloor = elev_get_floor_sensor_signal();
	if (elev_get_floor_sensor_signal()!= -1){
		switch (determ_dir(DIRN_DOWN, lastFloor, DOWN)){
			case 0:
			return FLOOR;
			break;

			default:
			return DOWN;
			break;
		}
	}
}

ElevatorState fsm_do_FLOOR(){
	elev_set_motor_direction(DIRN_STOP);
	elev_set_floor_indicator(elev_get_floor_sensor_signal());
	elev_set_door_open_lamp(1);
	if (timer_delay(3)){
		elev_set_door_open_lamp(0);
		return IDLE;
	}
	return STOP;
}

ElevatorState fsm_do_STOP(){
	elev_set_motor_direction(DIRN_STOP);
	elev_set_stop_lamp(1);
	register_reset_all();
	if(elev_get_floor_sensor_signal() != -1){
		elev_set_door_open_lamp(1);
	}
	while(1){
		if(!elev_get_stop_signal()){
		register_update();
		switch(determ_dir(lastDir, lastFloor, STOP)){
			case 1:
				return UP;
				break;
			case -1:
				return DOWN;
				break;
			case 0:
				return FLOOR;
				break;
		}

		}

	}
	
	return INIT;
}



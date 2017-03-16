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
	lastFloor = elev_get_floor_sensor_signal();
	elev_set_floor_indicator(lastFloor);
	register_update();
	if (elev_get_stop_signal()){
		return STOP;
	}
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
		break;

	}
}

ElevatorState fsm_do_UP(){
	elev_set_motor_direction(DIRN_UP);
	lastDir = DIRN_UP;
	register_update();
	if (elev_get_stop_signal()){
		return STOP;
	}
	if (elev_get_floor_sensor_signal()!= -1){
			lastFloor = elev_get_floor_sensor_signal();
			elev_set_floor_indicator(lastFloor);
		switch (determ_dir(DIRN_UP, lastFloor, UP)){
			case 0:
			return FLOOR;
			break;

			default:
			return UP;
			break;
		}
	}
	return UP;
}

ElevatorState fsm_do_DOWN(){
	elev_set_motor_direction(DIRN_DOWN);
	lastDir = DIRN_DOWN;
	register_update();
	if (elev_get_stop_signal()){
		return STOP;
	}
	if (elev_get_floor_sensor_signal()!= -1){
		lastFloor = elev_get_floor_sensor_signal();
		elev_set_floor_indicator(lastFloor);
		switch (determ_dir(DIRN_DOWN, lastFloor, DOWN)){
			case 0:
			return FLOOR;
			break;

			default:
			return DOWN;
			break;
		}
	}
	return DOWN;
}

ElevatorState fsm_do_FLOOR(){
	lastFloor = elev_get_floor_sensor_signal();
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
	printf("IN STOP\n");
	elev_set_motor_direction(DIRN_STOP);
	elev_set_stop_lamp(1);
	register_reset_all();
	if(elev_get_floor_sensor_signal() != -1){
		elev_set_door_open_lamp(1);
	}
	printf("In STOP%d\n", lastFloor);
	while(1){
		if(!elev_get_stop_signal()){
			register_update();
			switch(determ_dir(lastDir, lastFloor, STOP)){
				case 1:
					elev_set_stop_lamp(0);
					elev_set_door_open_lamp(0);
						return UP;
						break;
				case -1:
					elev_set_stop_lamp(0);
					elev_set_door_open_lamp(0);
					return DOWN;
					break;
				case 0:
					elev_set_stop_lamp(0);
					elev_set_door_open_lamp(0);
					return FLOOR;
					break;
				default:
					continue;
			}

		}

	}
	
	return INIT;
}



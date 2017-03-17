#include <stdio.h>
#include "FSM.h"
#include "timer.h"
#include "determ"

/////////////////////////////INIT/////////////////////////////////////////
ElevatorState fsm_do_INIT(){
	register_reset_all();
	if(elev_get_floor_sensor_signal() == -1){
		elev_set_motor_direction(DIRN_DOWN);
		return INIT;
	}
	else{
		elev_set_motor_direction(DIRN_STOP);
		if (elev_get_floor_sensor_signal() >= 0){
		 elev_set_floor_indicator(elev_get_floor_sensor_signal());
		}
		lastDir = DIRN_DOWN;
		return IDLE;
	}
}
/////////////////////////////////////////////////////////////////////////

///////////////////////////////IDLE//////////////////////////////////////
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

		case -1:
		return DOWN;

		case 0:
		return FLOOR;

		default:
		return IDLE;
	}
}
/////////////////////////////////////////////////////////////////////////

//////////////////////////////UP/////////////////////////////////////////
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

			default:
			return UP;
		}
	}
	return UP;
}
/////////////////////////////////////////////////////////////////////////

/////////////////////////////DOWN////////////////////////////////////////
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

			default:
			return DOWN;
		}
	}
	return DOWN;
}
/////////////////////////////////////////////////////////////////////////

//////////////////////////////FLOOR//////////////////////////////////////
ElevatorState fsm_do_FLOOR(){
	lastFloor = elev_get_floor_sensor_signal();
	elev_set_motor_direction(DIRN_STOP);
	elev_set_floor_indicator(elev_get_floor_sensor_signal());
	elev_set_door_open_lamp(1);
    time_t start = timer_start();
    while(1){
    	register_update();
    	for (int button = 0; button < N_BUTTONS; button ++){
        	if (register_get(button, lastFloor)){
        		register_reset_floor(lastFloor);
            	start = timer_start(); 
            	}
        	}
        	if(elev_get_stop_signal()){
            	return STOP;
        	}
        	else if(timer_is_time_out(start,3)){
            	return IDLE;
        	}
     }
    return FLOOR;
}
/////////////////////////////////////////////////////////////////////////

//////////////////////////////STOP///////////////////////////////////////
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
					elev_set_stop_lamp(0);
					elev_set_door_open_lamp(0);
					return UP;

				case -1:
					elev_set_stop_lamp(0);
					elev_set_door_open_lamp(0);
					return DOWN;

				case 0:
					elev_set_stop_lamp(0);
					elev_set_door_open_lamp(0);
					return FLOOR;

				case 69:
					return INIT;

				default:
					continue;
			}
		}
	}	
	return INIT;
}
/////////////////////////////////////////////////////////////////////////

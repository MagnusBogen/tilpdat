#include "FSM.h"

ElevatorState init(){
	enum ElevatorState state = INIT;

	if(elev_get_floor_sensor_signal() == -1){

		elev_set_motor_direction(DIRN_UP);
		

	}else{

		elev_set_motor_direction(DIRN_STOP);
		elev_set_floor_indicator(elev_get_floor_sensor_signal());

	}

	return state;
}
ElevatorState idleElevator(){
	enum ElevatorState state = IDLE;


	return state;
}

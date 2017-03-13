#include "FSM.h"
#include <stdio.h>


ElevatorState do_INIT(){
	reset_all();
	printf("In INIT\n");
	//printf("%d",elev_get_floor_sensor_signal());
	if(elev_get_floor_sensor_signal() == -1){
		elev_set_motor_direction(DIRN_DOWN);
		return INIT;
		

	}else{
		elev_set_motor_direction(DIRN_STOP);
		elev_set_floor_indicator(elev_get_floor_sensor_signal());
		dir = DIRN_DOWN;
		return IDLE;
	}
}


ElevatorState do_IDLE(){
	elev_set_motor_direction(DIRN_STOP);
	scan_buttons();
	if (stopButton){
		return STOP;
	}
	FSM_floor = elev_get_floor_sensor_signal();
	switch (next_dir(dir, FSM_floor, IDLE)){
		case 1:
		return UP;
		break;

		case -1:
		return DOWN;
		break;

		default:
		return IDLE;

	}


	return IDLE; //(//)
}

ElevatorState do_UP(){
	elev_set_motor_direction(DIRN_UP);
	dir = DIRN_UP;
	scan_buttons();
	if (stopButton){
		return STOP;
	}
	FSM_floor = elev_get_floor_sensor_signal();
	if (elev_get_floor_sensor_signal()!= -1){
		switch (next_dir(DIRN_UP, FSM_floor, UP)){
			case 1:
			return UP;
			break;

			case -1:
			return DOWN;
			break;

			case 0:
			return IDLE;
			
			default:
			return IDLE;
		}
	}
	printf("In UP\n");

	return UP;
}

ElevatorState do_DOWN(){
	dir = DIRN_DOWN;
	elev_set_motor_direction(DIRN_DOWN);
	scan_buttons();
	if (elev_get_stop_signal()){
		return STOP;
	}
	FSM_floor = elev_get_floor_sensor_signal();
	if (elev_get_floor_sensor_signal()!= -1){
		switch (next_dir(DIRN_DOWN, FSM_floor, DOWN)){
			case 1:
			return UP;
			break;

			case -1:
			return DOWN;
			break;

			default:
			return IDLE;

		}
	}
	printf("In UP\n");

	return DOWN;
}

ElevatorState do_FLOOR(){
	printf("In FLOOR\n");
	return IDLE;
}

ElevatorState do_STOP(){
	printf("In STOP\n");
	elev_set_motor_direction(DIRN_STOP);
	reset_all();
	while(1){
		if(!elev_get_stop_signal()){
			break;
		}

	}
	
	return IDLE;
}

ElevatorState test_dir(){
	int value;
	//printf("In IDLE\n");
	//scan_buttons();
	print_register();
	buttonRegister[BUTTON_CALL_DOWN][3] = true;
	//buttonRegister[BUTTON_CALL_DOWN][1] = true;
	print_register();
	value = next_dir(DIRN_DOWN, 1, IDLE);
	printf("%d\n", value);



	return IDLE;
}

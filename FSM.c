#include "FSM.h"
#include "timer.h"
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
		if (elev_get_floor_sensor_signal() >= 0){
		 elev_set_floor_indicator(elev_get_floor_sensor_signal());
		}
		dir = DIRN_DOWN;
		return IDLE;
	}
}


ElevatorState do_IDLE(){
	//printf("In state IDLE\n");
	scan_buttons();
	if (elev_get_stop_signal()){
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

		case 0:
		return FLOOR;
		break;

		default:
		return IDLE;

	}


	return IDLE; //(//)
}

ElevatorState do_UP(){
	//printf("In UP\n");
	elev_set_motor_direction(DIRN_UP);
	dir = DIRN_UP;
	scan_buttons();
	if (elev_get_stop_signal()){
		return STOP;
	}
	FSM_floor = elev_get_floor_sensor_signal();
	if (elev_get_floor_sensor_signal()!= -1){
		switch (next_dir(DIRN_UP, FSM_floor, UP)){
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

ElevatorState do_FLOOR(){
	printf("In FLOOR %d\n", elev_get_floor_sensor_signal() + 1);
	elev_set_motor_direction(DIRN_STOP);

	elev_set_floor_indicator(elev_get_floor_sensor_signal());

	elev_set_door_open_lamp(1);
	if (timer_delay(3)){
		elev_set_door_open_lamp(0);
		return IDLE;
	}
	return STOP;
}

ElevatorState do_STOP(){
	printf("In STOP\n");
	elev_set_motor_direction(DIRN_STOP);
	elev_set_stop_lamp(1);
	reset_all();
	while(1){
		scan_buttons();
		for (int b = 0; b < N_BUTTONS; b++){
			for (int f = 0; f < N_FLOORS; f++){
					if (buttonRegister[b][f]){
						elev_set_stop_lamp(0);
						return INIT;

					}

					

	

			}

		}
	}
	
	return INIT;
}

ElevatorState test_dir(){
	int value;
	//printf("In IDLE\n");
	//scan_buttons();
	print_register();
	buttonRegister[BUTTON_CALL_UP][0] = true;
	//buttonRegister[BUTTON_CALL_DOWN][1] = true;
	print_register();
	value = next_dir(DIRN_DOWN, 2, IDLE);
	printf("%d\n", value);



	return IDLE;
}

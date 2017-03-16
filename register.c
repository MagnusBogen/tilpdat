#include "register.h"
#include <stdio.h>
#include "elev.h"


void register_set(int button, int floor){

}

bool register_get(int button, int floor)


void register_reset_floor(int floor){
	for(button=0;button<N_BUTTONS;button++){
		register_reset(button,floor);
	}
}



bool register_empty_above(int floor){
	if (floor == 3){
		return true;
	}
	for (int b = 0; b < N_BUTTONS; b++){
		for (int f = floor+1; f < N_FLOORS; f++){
			if(buttonRegister[b][f]){
				return false;
			}
		}
	}
	return true;
}

bool register_empty_below(int floor){
	if (floor == 0){
		return true;
	}
	for (int b = 0; b < N_BUTTONS; b++){
		for (int f = floor-1; f >= 0; f--){
			if(buttonRegister[b][f]){
				return false;
			}
		}
	}
	return true;
}

void register_reset(int Button, int Floor){
	if (!((Floor==3 && Button==BUTTON_CALL_UP) || (Floor==0 && Button==BUTTON_CALL_DOWN))){
		printf("In reset\n");
		buttonRegister[Button][Floor] = false;
		elev_set_button_lamp(Button,Floor, 0);
	}
}


void register_reset_all(){
	printf("In rese_all");
	for (int b = 0; b < N_BUTTONS; b++){
		for (int f = 0; f < N_FLOORS; f++){
			if ((f==3 && b==BUTTON_CALL_UP) || (f==0 && b==BUTTON_CALL_DOWN)){
				//erfer
			}
			else{
				printf("Reset: %d%d", b, f);
				buttonRegister[b][f] = false;
				elev_set_button_lamp(b,f, false);
		}
	}

	}
}


void register_update(){
//	if (elev_get_floor_sensor_signal() >= 0){
//		 elev_set_floor_indicator(elev_get_floor_sensor_signal());
//		}
	for (int b = 0; b < N_BUTTONS; b++){
		for (int f = 0; f < N_FLOORS; f++){
			if ((f==3 && b==BUTTON_CALL_UP) || (f==0 && b==BUTTON_CALL_DOWN)){
				continue;
				}
			
			if(elev_get_button_signal(b,f)){
					buttonRegister[b][f] = true;
					elev_set_button_lamp(b,f, buttonRegister[b][f]);
			}
				
				
		}

	}
}




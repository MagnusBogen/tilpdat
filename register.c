#include <stdio.h>
#include "register.h"
#include "elev.h"


void register_set(int button, int floor){
	buttonRegister[button][floor] = true;
}

bool register_get(int button, int floor){
	return buttonRegister[button][floor];

}

void register_reset_floor(int floor){
	for(int button=0;button<N_BUTTONS;button++){
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
		buttonRegister[Button][Floor] = false;
		elev_set_button_lamp(Button,Floor, 0);
	}
}

void register_reset_all(){
	printf("In rese_all");
	for (int b = 0; b < N_BUTTONS; b++){
		for (int f = 0; f < N_FLOORS; f++){
			if (!((f==3 && b==BUTTON_CALL_UP) || (f==0 && b==BUTTON_CALL_DOWN))){
				buttonRegister[b][f] = false;
				elev_set_button_lamp(b,f, false);
			}
		}
	}
}

void register_update(){
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
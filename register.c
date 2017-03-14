#include "register.h"
#include <stdio.h>
#include "elev.h"
#include "LightStates.h"


bool empty_above(int floor){
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
bool empty_below(int floor){
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

void set(int Button, int Floor){
	buttonRegister[Button][Floor] = true;
}

void reset(int Button, int Floor){
	if (!((Floor==3 && Button==BUTTON_CALL_UP) || (Floor==0 && Button==BUTTON_CALL_DOWN))){
		printf("In reset\n");
		buttonRegister[Button][Floor] = false;
		elev_set_button_lamp(Button,Floor, 0);
	}
}


bool get(int Button, int Floor){
	return buttonRegister[Button][Floor];	
}


void reset_all(){
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


void print_register(){
	for (int b = 0; b < N_BUTTONS; b++){
		printf("\n");
		for (int f = 0; f < N_FLOORS; f++){
			printf("Button/floor/value: %d %d",b,f);
			printf(" %d", buttonRegister[b][f]);
			printf("\n");
	}
}
}



void scan_buttons(){
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

//up = 0, down = 1, command = 2
int next_dir(int lastDir, int lastFloor, int state){

////////////////////////////UP///////////////////////////////////////////
	if (state == 2){
		//printf("In UP\n");
		for (int f=N_FLOORS-1; f >= 0; f--){

			if (buttonRegister[2][f] && lastFloor == f)	{
				reset(2,f);
				reset(0,f);
				if (empty_above(f)){
					reset(1,f);
				}
				return 0;
			}

			else if(buttonRegister[0][f] && lastFloor == f)	{
				reset(0,f);
				reset(2,f);
				if (empty_above(f)){
					reset(1,f);
				}
				return 0;
			}

			else if(buttonRegister[1][f] && lastFloor == f && empty_above(f)){
				reset(1,f);
				return 0;
			}
		
		}
	}

////////////////////////////DOWN//////////////////////////////////////////
	else if (state == 3) {
		//printf("In DOWN\n");
		for (int f=0; f < N_FLOORS; f++){

			if (buttonRegister[2][f] && lastFloor == f)	{
				reset(2,f);
				reset(1,f);
				if (empty_below(f)){
					reset(0,f);
				}
				return 0;
			}

			else if(buttonRegister[1][f] && lastFloor == f)	{
				reset(1,f);
				reset(2,f);
				if (empty_above(f)){
					reset(0,f);
				}
				return 0;
			}

			else if(buttonRegister[0][f] && lastFloor == f && empty_below(f))	{
				reset(0,f);
				return 0;
			}

		}

	}
////////////////////////////IDLE//////////////////////////////////////////
	else if (state == 1){
		//printf("In IDLE\n");
		////////////////////DIRN_UP///////////////////////////////////////
		if (lastDir == DIRN_UP){
			//printf("DIRN_UP\n");

			for (int f=N_FLOORS-1; f >= 0; f--){
				if (buttonRegister[2][f]){
					if (f>lastFloor)	{return 1;}
					else if (f == lastFloor){
						reset(2,f);
						return 0;
					}
					else {return -1;}
			}


				else if(buttonRegister[0][f]){
					if (f>lastFloor)	{return 1;}
					else if (f == lastFloor){
						reset(0,f);
						return 0;
					}
					else {return -1;}
				}

				else if(buttonRegister[1][f]){
					if (f>lastFloor)	{return 1;}
					else if (f == lastFloor){
						reset(1,f);
						return 0;
					}
					else {return -1;}
				}
		
		}
		}
		////////////////////DIRN_DOWN//////////////////////////////////////
		else if (lastDir == DIRN_DOWN){
			//printf("DIRN_DOWN\n");

			for (int f=0; f < N_FLOORS; f++){
				if (buttonRegister[2][f]){
					if (f>lastFloor)	{return 1;}
					else if (f == lastFloor){
						reset(2,f);
						return 0;
					}
					else {return -1;}
			}


				else if(buttonRegister[0][f]){
					if (f>lastFloor)	{return 1;}
					else if (f == lastFloor){
						reset(0,f);
						return 0;
					}
					else {return -1;}
				}

				else if(buttonRegister[1][f]){
					if (f>lastFloor)	{return 1;}
					else if (f == lastFloor){
						reset(1,f);
						return 0;}
					else {return -1;}
				}
		
		}
		}
		


	}
	//printf("FERDIG\n");
	return 5;
}



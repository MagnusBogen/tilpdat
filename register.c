#include "register.h"
#include <stdio.h>


void set(int Floor, int Button ){
	buttonRegister[Floor][Button] = true;
}

void reset(int Floor, int Button){
	buttonRegister[Floor][Button] = false;
}


bool get(int Floor, int Button){
			return buttonRegister[f][b];	
}


void reset_all(){
	for (int f = 0; f < N_FLOORS; f++){
		for (int b = 0; b < N_BUTTONS; b++){
			buttonRegister[f][b] = false;
		}
	}
}


#include "determ.h"
#include "register.h"
#include <stdio.h>

//up = 0, down = 1, command = 2
int determ_dir(int lastDir, int floor, int state){

////////////////////////////UP///////////////////////////////////////////
	if (state == 2){
		//printf("In UP\n");
		for (int f=N_FLOORS-1; f >= 0; f--){

			if (buttonRegister[2][f] && lastFloor == f)	{
				register_reset_floor(f);
				return 0;
			}

			else if(buttonRegister[0][f] && lastFloor == f)	{
				reset(0,f);
				reset(2,f);
				reset(1,f);
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
				reset(0,f);
				return 0;
			}

			else if(buttonRegister[1][f] && lastFloor == f)	{
				reset(1,f);
				reset(2,f);
				reset(0,f);
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
						reset(1,f);
						reset(2,f);
						reset(0,f);
						return 0;
					}
					else {return -1;}
			}


				else if(buttonRegister[0][f]){
					if (f>lastFloor)	{return 1;}
					else if (f == lastFloor){
						reset(1,f);
						reset(2,f);
						reset(0,f);
						return 0;
					}
					else {return -1;}
				}

				else if(buttonRegister[1][f]){
					if (f>lastFloor)	{return 1;}
					else if (f == lastFloor){
						reset(1,f);
						reset(2,f);
						reset(0,f);
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
						reset(1,f);
						reset(2,f);
						reset(0,f);
						return 0;
					}
					else {return -1;}
			}


				else if(buttonRegister[0][f]){
					if (f>lastFloor)	{return 1;}
					else if (f == lastFloor){
						reset(1,f);
						reset(2,f);
						reset(0,f);
						return 0;
					}
					else {return -1;}
				}

				else if(buttonRegister[1][f]){
					if (f>lastFloor)	{return 1;}
					else if (f == lastFloor){
						reset(1,f);
						reset(2,f);
						reset(0,f);
						return 0;}
					else {return -1;}
				}
		
		}
		}
		


	}
	//printf("FERDIG\n");
	return 5;
}
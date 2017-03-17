#include "determ.h"
#include "register.h"
#include <stdio.h>


int determ_dir(int lastDir, int lastFloor, int state){
////////////////////////////UP///////////////////////////////////////////
	if (state == UP){
		for (int f=N_FLOORS-1; f >= 0; f--){

			if (register_get(2,f) && lastFloor == f)	{
				register_reset_floor(f);
				return 0;
			}
			else if(register_get(0,f) && lastFloor == f)	{
				register_reset_floor(f);
				return 0;
			}
			else if(register_get(1,f) && lastFloor == f && register_empty_above(f)){
				register_reset(1,f);
				return 0;
			}
		}
	}
//////////////////////////////////////////////////////////////////////////

////////////////////////////DOWN//////////////////////////////////////////
	else if (state == DOWN) {
		for (int f=0; f < N_FLOORS; f++){

			if (register_get(2,f) && lastFloor == f)	{
				register_reset_floor(f);
				return 0;
			}
			else if(register_get(1,f) && lastFloor == f)	{
				register_reset_floor(f);
				return 0;
			}
			else if(register_get(0,f) && lastFloor == f && register_empty_below(f))	{
				register_reset(0,f);
				return 0;
			}
		}
	}
//////////////////////////////////////////////////////////////////////////

////////////////////////////IDLE//////////////////////////////////////////
	else if (state == IDLE){
		////////////////////DIRN_UP///////////////////////////////////////
		if (lastDir == DIRN_UP){
			for (int f=N_FLOORS-1; f >= 0; f--){

				if (register_get(2,f)){
					if (f>lastFloor)	{return 1;}
					else if (f == lastFloor){
						register_reset_floor(f);
						return 0;
					}
					else {return -1;}
			}
				else if(register_get(0,f)){
					if (f>lastFloor)	{return 1;}
					else if (f == lastFloor){
						register_reset_floor(f);
						return 0;
					}
					else {return -1;}
				}
				else if(register_get(1,f)){
					if (f>lastFloor)	{return 1;}
					else if (f == lastFloor){
						register_reset_floor(f);
						return 0;
					}
					else {return -1;}
				}
			}
		}
		///////////////////////////////////////////////////////////////////

		////////////////////DIRN_DOWN//////////////////////////////////////
		else if (lastDir == DIRN_DOWN){
			for (int f=0; f < N_FLOORS; f++){
				if (register_get(2,f)){
					if (f>lastFloor)	{return 1;}
					else if (f == lastFloor){
						register_reset_floor(f);
						return 0;
					}
					else {return -1;}
			}
				else if(register_get(0,f)){
					if (f>lastFloor)	{return 1;}
					else if (f == lastFloor){
						register_reset_floor(f);
						return 0;
					}
					else {return -1;}
				}
				else if(register_get(1,f)){
					if (f>lastFloor)	{return 1;}
					else if (f == lastFloor){
						register_reset_floor(f);
						return 0;}
					else {return -1;}
				}	
			}
		}
		///////////////////////////////////////////////////////////////////
	}
//////////////////////////////////////////////////////////////////////////

////////////////////////////STOP//////////////////////////////////////////
		else if(state == STOP){
			if (lastFloor == -1){
				printf("ERROR! LastFloor = -1!\n");
				return 69;
			}
			for (int f = 0; f < N_FLOORS; f++){
				for(int b = 0; b < N_BUTTONS; b++){
					if(register_get(b,f)){
						if(f>lastFloor){
							return 1;
						}
						else if(f<lastFloor){
							return -1;
						}
						else if(f==lastFloor){
							if (elev_get_floor_sensor_signal() != -1){
								return 0;
							}
							else if(lastDir == -1){
								return 1;
							}

							else if(lastDir == 1){
								return -1;
							}
						
						}
					}
				}
			}
		}
	return 69;
//////////////////////////////////////////////////////////////////////////
}
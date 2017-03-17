#include <stdio.h>
#include "elev.h"

/*	Typedef for use in return types for functions            */
typedef enum bool{false, true}bool;

/*	The buttonRegister holds the order information	
	true if button has been pushed and false if not          */
bool buttonRegister[N_BUTTONS][N_FLOORS]; 


/*	Sets button == true to register  */
void register_set(int Button, int Floor);


/*	Returns value of button in register  
	true if button has been pushed and false if not           */
bool register_get(int Button, int Floor);


/*	Resets all buttons at floor  
	sets all values in button register to false               */
void register_reset_floor(int floor);


/*	Resets button at specified floor  
	sets all values of the floor in button register to false  */
void register_reset(int Button, int Floor);


/*	Resets all buttons at all floors  
	sets the value of all buttons in button register to false */
void register_reset_all();


/*	Updates register based on input from elev
	sets button in button register to true if pushed          */
void register_update();


/*	Returns true if the register is empty for all floors ABOVE the specified floor  */
bool register_empty_above(int floor);


/*	Returns true if the register is empty for all floors BELOW the specified floor  */
bool register_empty_below(int floor);
#include <time.h>
#include <stdio.h>
#include "elev.h"


typedef enum bool{false, true}bool;
bool buttonRegister[N_BUTTONS][N_FLOORS]; //etg x buttonType

/*	Sets button to register  */
void register_set(int Button, int Floor);

/*	Returns true if button is true in register  */
bool register_get(int Button, int Floor);

/*	Resets all buttons at floor  */
void register_reset_floor(int floor);

/*	Resets button at floor  */
void register_reset(int Button, int Floor);

/*	Resets all buttons at all floors  */
void register_reset_all();

/*	Updates register based on input from elev  */
void register_update();

/*	Returns true if register is empty ABOVE the specified floor  */
bool register_empty_above(int floor);

/*	Returns true if register is empty BELOW the specified floor  */
bool register_empty_below(int floor);
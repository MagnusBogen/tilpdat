#include <time.h>
#include <stdio.h>
#include "elev.h"


typedef enum bool{false, true}bool;
bool buttonRegister[N_BUTTONS][N_FLOORS]; //etg x buttonType

void register_reset_floor(int floor);
void register_reset(int Button, int Floor);
void register_reset_all();
void register_update();
bool register_empty_above(int floor);
bool register_empty_below(int floor);
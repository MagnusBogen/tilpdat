#include <time.h>
#include <stdio.h>
#include "elev.h"


typedef enum bool{false, true}bool;
bool buttonRegister[N_BUTTONS][N_FLOORS]; //etg x buttonType


void set(int Button, int Floor);
void reset(int Button, int Floor);
void reset_all();
void scan_buttons();
int next_dir(int lastDir, int lastFloor,  int state);
bool empty_above(int floor);
bool empty_below(int floor);
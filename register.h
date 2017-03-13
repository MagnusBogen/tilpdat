#include <time.h>
#include <stdio.h>
#include "elev.h"


typedef enum bool{false, true}bool;
bool buttonRegister[N_BUTTONS][N_FLOORS]; //etg x buttonType
int stopButton;

void set(int Button, int Floor);
bool get(int Button, int Floor);
void reset(int Button, int Floor);
void reset_all();
void scan_buttons();
int next_dir(int lastDir, int lastFloor,  int state);
void print_register();
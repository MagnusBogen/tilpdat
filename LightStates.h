#pragma once
// Light States
#include <stdio.h>
#include "elev.h"
struct LightStates {
	enum ButtonType {
		UP_FIRST_FLOOR,
		UP_SECOND_FLOOR, DOWN_SECOND_FLOOR,
		UP_THIRD_FLOOR, DOWN_THIRD_FLOOR,
		DOWN_FOURTH_FLOOR,
		ELEVATOR_PANEL_ONE,
		ELEVATOR_PANEL_TWO,
		ELEVATOR_PANEL_THREE,
		ELEVATOR_PANEL_FOUR,
		STOP
	} ButtonType;
	int buttonStates[11];
	int doorlightState;
	int lastFloor;
};

int getLightState(enum ButtonType button, struct LightStates* lightStateObject);
int getDoorlightState(struct LightStates* lightStateObject);

void setLightState(enum ButtonType button, int state, struct LightStates* lightStateObject);

void initLightStates(struct LightStates* lightStateObject);
void updateLightStates(struct LightStates* lightStateObject);


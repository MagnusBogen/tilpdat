#include "LightStates.h"

int getLightState(enum ButtonType button, struct LightStates* lightStateObject) {
	if (button > STOP) {
		printf("Error: LightStates.c->getLightState->if(button > lightStateObject.STOP), argument parameters is invalid!");
		return (-1);
	}
	return lightStateObject->buttonStates[button];
}


int getDoorlightState(struct LightStates* lightStateObject) {
	return lightStateObject->doorlightState;
}

void setLightState(enum ButtonType button, int state, struct LightStates* lightStateObject) {
	if (button > STOP) {
		printf("Error: LightStates.c->setLightState->if(button > lightStateObject.STOP), argument parameters is invalid!");
	}
	else {
		lightStateObject->buttonStates[button] = state;
	}
}

void setDoorlightState(int state, struct LightStates* lightStateObject) {
	lightStateObject->doorlightState = state;
}

void initLightStates(struct LightStates* lightStateObject) {
	lightStateObject->lastFloor = elev_get_floor_sensor_signal();
	int arrayLength = sizeof(lightStateObject->buttonStates) / sizeof(int);
	
	if (elev_get_floor_sensor_signal() != -1) lightStateObject->lastFloor = elev_get_floor_sensor_signal();
	if (lightStateObject->lastFloor != -1) elev_set_floor_indicator(lightStateObject->lastFloor);
	

	elev_set_door_open_lamp(0);
	elev_set_stop_lamp(0);

	for (int element = 0; element < arrayLength; element++) {
		lightStateObject->buttonStates[element] = 0;
	}
	
}


void updateLightStates(struct LightStates* lightStateObject) {
	int arrayLength = sizeof(lightStateObject->buttonStates) / sizeof(int);

	if (elev_get_floor_sensor_signal() != -1) lightStateObject->lastFloor = elev_get_floor_sensor_signal();
	if (lightStateObject->lastFloor <= -1) elev_set_floor_indicator(lightStateObject->lastFloor);

	elev_set_door_open_lamp(getDoorlightState(lightStateObject));

	for (int element = 0; element < arrayLength; element++) {
		printf("%d", lightStateObject->buttonStates[element]);
		switch (element) {
		case UP_FIRST_FLOOR:
			elev_set_button_lamp(BUTTON_CALL_UP, 0, lightStateObject->buttonStates[element]);
			break;
		case UP_SECOND_FLOOR:
			elev_set_button_lamp(BUTTON_CALL_UP, 1, lightStateObject->buttonStates[element]);
			break;
		case DOWN_SECOND_FLOOR:
			elev_set_button_lamp(BUTTON_CALL_DOWN, 1, lightStateObject->buttonStates[element]);
			break;
		case UP_THIRD_FLOOR:
			elev_set_button_lamp(BUTTON_CALL_UP, 2, lightStateObject->buttonStates[element]);
			break;
		case DOWN_THIRD_FLOOR:
			elev_set_button_lamp(BUTTON_CALL_DOWN, 2, lightStateObject->buttonStates[element]);
			break;
		case DOWN_FOURTH_FLOOR:
			elev_set_button_lamp(BUTTON_CALL_DOWN, 3, lightStateObject->buttonStates[element]);
			break;
		case ELEVATOR_PANEL_ONE:
			elev_set_button_lamp(BUTTON_COMMAND, 0, lightStateObject->buttonStates[element]);
			break;
		case ELEVATOR_PANEL_TWO:
			elev_set_button_lamp(BUTTON_COMMAND, 1, lightStateObject->buttonStates[element]);
			break;
		case ELEVATOR_PANEL_THREE:
			elev_set_button_lamp(BUTTON_COMMAND, 2, lightStateObject->buttonStates[element]);
			break;
		case ELEVATOR_PANEL_FOUR:
			elev_set_button_lamp(BUTTON_COMMAND, 3, lightStateObject->buttonStates[element]);
			break;
		case STOP:
			elev_set_stop_lamp(lightStateObject->buttonStates[element]);
			break;

		}
	}
}


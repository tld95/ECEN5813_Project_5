/*
 * PES Project Four Functions Enum List Header Code
 * Tristan Duenas
 * References:
 */

#ifndef __FUNCTION_NAMES_H__
#define __FUNCTION_NAMES_H__

#include <string.h>

#define MAX_NAME_LENGTH 100

typedef enum function_names
{
	// Color Sensor Control
	COLOR_SENSOR_INIT = 0,
	COLOR_SENSOR_POST_TEST = 1,
	GET_COLOR_SENSOR_REGISTER_VALUE = 2,
	// I2C Control
	I2C_WAIT = 3,
	I2C_TRANSMIT = 4,
	// LED Control
	LED_CONTROL = 5,
	// State Machine Control
	RUN_STATE_MACHINES = 6,
	RUN_STATE_MACHINE_ONE = 7,
	RUN_STATE_MACHINE_TWO = 8,
	// Time Control
	DELAY = 9,
	MAIN = 10
} Function_Names;

void getFunctionName(Function_Names function, char* name);

#endif

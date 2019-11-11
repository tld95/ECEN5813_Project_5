/*
 * PES Project Four Functions Enum List Source Code
 * Tristan Duenas
 * References:
 */

#include "functions_enum_list.h"

void getFunctionName(Function_Names function, char* name)
{
	switch(function)
	{
		case COLOR_SENSOR_INIT:
			strcpy(name, "Color Sensor Init");
			break;
		case COLOR_SENSOR_POST_TEST:
			strcpy(name, "Color Sensor POST Test");
			break;
		case GET_COLOR_SENSOR_REGISTER_VALUE:
			strcpy(name, "Get Color Sensor Register Value");
			break;
		case I2C_WAIT:
			strcpy(name, "I2C Wait");
			break;
		case I2C_TRANSMIT:
			strcpy(name, "I2C Transmit");
			break;
		case LED_CONTROL:
			strcpy(name, "LED Control");
			break;
		case RUN_STATE_MACHINES:
			strcpy(name, "Run State Machine");
			break;
		case RUN_STATE_MACHINE_ONE:
			strcpy(name, "Run State Machine One");
			break;
		case RUN_STATE_MACHINE_TWO:
			strcpy(name, "Run State Machine Two");
			break;
		case DELAY:
			strcpy(name, "Delay");
			break;
		case MAIN:
			strcpy(name, "Main");
			break;
		default:
			// Do nothing
			break;
	}
}

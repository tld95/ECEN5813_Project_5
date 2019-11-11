/*
 *  PES Project Four State Machine Control source code implementation
 *	Tristan Duenas
 */


#include "state_machines.h"

void run_state_machines()
{
	state_machine_states currentState = STATE_ONE;
	while ((currentState != DISCONNECTED) && (currentState != COMPLETED))
	{
		switch(currentState)
		{
			case STATE_ONE:
				run_state_machine_one(&currentState);
				break;
			case STATE_TWO:
				run_state_machine_two(&currentState);
				break;
			default:
				// Do nothing
				break;
		}
	}

	switch(currentState)
	{
		case DISCONNECTED:
			Log_string(STATUS_LEVEL, RUN_STATE_MACHINES, "Temp 102 Disconnected");
			break;
		case COMPLETED:
			Log_string(STATUS_LEVEL, RUN_STATE_MACHINES, "State Machine One and Two Completed");
			break;
		default:
			// Do nothing
			break;
	}
}

void run_state_machine_one(state_machine_states* nextState)
{
	Log_string(STATUS_LEVEL, RUN_STATE_MACHINE_ONE, "Starting State Machine One.");
	uint32_t timeoutCount = 0;
	uint32_t valuesAveraged = 1;
	uint32_t averageValue = 0;
	uint32_t previousValue = 0;
	uint32_t totalValuesAdded = 0;
	status tempStatus = PASSED;
	while ((tempStatus == PASSED) && (timeoutCount < 4))
	{
		uint8_t value = 0;
		value = getColorSensorRegisterValue(&tempStatus, RED_REGISTER_LOW);
		totalValuesAdded += value;
		averageValue = totalValuesAdded / valuesAveraged;
		valuesAveraged++;
		// Temp 102 Disconnected or Temp Alert
		if ((tempStatus == FAILED) || value < 0)
		{
			led_control(RED);
			*nextState = DISCONNECTED;
		}
		else
		{
			Log_string(DEBUG_LEVEL, RUN_STATE_MACHINE_ONE, "Previous Red Value:");
			Log_integer(DEBUG_LEVEL, RUN_STATE_MACHINE_ONE, previousValue);
			Log_string(DEBUG_LEVEL, RUN_STATE_MACHINE_ONE, "Current Red Value");
			Log_integer(DEBUG_LEVEL, RUN_STATE_MACHINE_ONE, value);
			Log_string(STATUS_LEVEL, RUN_STATE_MACHINE_ONE, "Average Red Value:");
			Log_integer(STATUS_LEVEL, RUN_STATE_MACHINE_ONE, averageValue);
		}
		timeoutCount++;
		previousValue = value;
	}
	if (tempStatus == PASSED)
	{
		*nextState = STATE_TWO;
	}
}

void run_state_machine_two(state_machine_states* nextState)
{
	Log_string(STATUS_LEVEL, RUN_STATE_MACHINE_TWO, "Starting State Machine Two.");
	uint32_t timeoutCount = 0;
	uint32_t valuesAveraged = 1;
	uint32_t averageValue = 0;
	uint32_t previousValue = 0;
	uint32_t totalValuesAdded = 0;
	status tempStatus = PASSED;
	while ((tempStatus == PASSED) && (timeoutCount < 4))
	{
		uint8_t value = 0;
		value = getColorSensorRegisterValue(&tempStatus, RED_REGISTER_LOW);
		totalValuesAdded += value;
		averageValue = totalValuesAdded / valuesAveraged;
		valuesAveraged++;
		// Temp 102 Disconnected or Temp Alert
		if ((tempStatus == FAILED) || value < 0)
		{
			*nextState = DISCONNECTED;
		}
		else
		{
			Log_string(DEBUG_LEVEL, RUN_STATE_MACHINE_TWO, "Previous Red Value:");
			Log_integer(DEBUG_LEVEL, RUN_STATE_MACHINE_TWO, previousValue);
			Log_string(STATUS_LEVEL, RUN_STATE_MACHINE_TWO, "Current Red Value");
			Log_integer(STATUS_LEVEL, RUN_STATE_MACHINE_TWO, value);
			Log_string(STATUS_LEVEL, RUN_STATE_MACHINE_TWO, "Average Red Value:");
			Log_integer(STATUS_LEVEL, RUN_STATE_MACHINE_TWO, averageValue);
		}
		timeoutCount++;
		previousValue = value;
	}
	if (tempStatus == PASSED)
	{
		*nextState = COMPLETED;
	}
}

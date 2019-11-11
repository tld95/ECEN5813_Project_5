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
			Log_string("Temp 102 Disconnected");
			break;
		case COMPLETED:
			Log_string("State Machine One and Two Completed");
			break;
		default:
			// Do nothing
			break;
	}
}

void run_state_machine_one(state_machine_states* nextState)
{
	Log_string("Starting State Machine One.");
	uint32_t timeoutCount = 0;
	uint32_t valuesAveraged = 1;
	uint32_t averageValue = 0;
	uint32_t previousValue = 0;
	uint32_t totalValuesAdded = 0;
	status tempStatus = PASSED;
	while ((tempStatus == PASSED) && (timeoutCount < 4))
	{
		uint8_t value = 0;
		value = getRegValue(&tempStatus, RED_REGISTER_LOW);
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
			Log_string("Previous Red Value:");
			Log_integer(previousValue);
			Log_string("Current Red Value");
			Log_integer(value);
			Log_string("Average Red Value:");
			Log_integer(averageValue);
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
	Log_string("Starting State Machine Two.");
	uint32_t timeoutCount = 0;
	uint32_t valuesAveraged = 1;
	uint32_t averageValue = 0;
	uint32_t previousValue = 0;
	uint32_t totalValuesAdded = 0;
	status tempStatus = PASSED;
	while ((tempStatus == PASSED) && (timeoutCount < 4))
	{
		uint8_t value = 0;
		value = getRegValue(&tempStatus, RED_REGISTER_LOW);
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
			Log_string("Previous Red Value:");
			Log_integer(previousValue);
			Log_string("Current Red Value");
			Log_integer(value);
			Log_string("Average Red Value:");
			Log_integer(averageValue);
		}
		timeoutCount++;
		previousValue = value;
	}
	if (tempStatus == PASSED)
	{
		*nextState = COMPLETED;
	}
}

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
	uint32_t averageTemp = 0;
	uint32_t previousTemp = 0;
	uint32_t totalTempAdded = 0;
	status tempStatus = PASSED;
	while ((tempStatus == PASSED) && (timeoutCount < 4))
	{
		uint8_t temp = 0;
		temp = getRegValue(&tempStatus, 0x16);
		totalTempAdded += temp;
		averageTemp = totalTempAdded / valuesAveraged;
		valuesAveraged++;
		// Temp 102 Disconnected or Temp Alert
		if ((tempStatus == FAILED) || temp < 0)
		{
			*nextState = DISCONNECTED;
		}
		else
		{
			Log_string("Previous Temp:");
			Log_integer(previousTemp);
			Log_string("Current Temp");
			Log_integer(temp);
			Log_string("Average Temp:");
			Log_integer(averageTemp);
		}
		delay(1000);
		timeoutCount++;
		previousTemp = temp;
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
	uint32_t averageTemp = 0;
	uint32_t previousTemp = 0;
	uint32_t totalTempAdded = 0;
	status tempStatus = PASSED;
	while ((tempStatus == PASSED) && (timeoutCount < 4))
	{
		uint8_t temp = 0;
		temp = getRegValue(&tempStatus, 0x16);
		totalTempAdded += temp;
		averageTemp = totalTempAdded / valuesAveraged;
		valuesAveraged++;
		// Temp 102 Disconnected or Temp Alert
		if ((tempStatus == FAILED) || (temp < 0))
		{
			*nextState = DISCONNECTED;
		}
		else
		{
			Log_string("Previous Temp:");
			Log_integer(previousTemp);
			Log_string("Current Temp");
			Log_integer(temp);
			Log_string("Average Temp:");
			Log_integer(averageTemp);
		}
		delay(1000);
		timeoutCount++;
		previousTemp = temp;
	}
	if (tempStatus == PASSED)
	{
		*nextState = COMPLETED;
	}
}

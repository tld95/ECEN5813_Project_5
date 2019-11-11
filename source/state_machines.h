
/*
 *  PES Project Four State Machine Control header code implementation
 *	Tristan Duenas
 */

#ifndef __STATE_MACHINE_CONTROL_H__
#define __STATE_MACHINE_CONTROL_H__

#include <color_sensor_control.h>
#include <stdint.h>
#include "logger.h"
#include "timing_control.h"

typedef enum state_machine_states
{
	STATE_ONE,
	STATE_TWO,
	DISCONNECTED,
	COMPLETED
} state_machine_states;

void run_state_machines();
void run_state_machine_one(state_machine_states* nextState);
void run_state_machine_two(state_machine_states* nextState);

#endif

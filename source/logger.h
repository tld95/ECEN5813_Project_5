/*
 * PES Project Three display logger header code implementation
 * Tristan Duenas
 * References:
 */

#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#if defined(FB_RUN) || defined(FB_DEBUG)
#include "fsl_debug_console.h"
#endif

typedef enum logStatus
{
	DISABLED = 0,
	ENABLED = 1
} logStatus;

// Enables logging
void Log_enable();
// Disables logging
void Log_disable();
// Returns current logging enabled/disabled status
logStatus Log_status();
// Logs a block of data from memory
void Log_data(uint8_t *address, size_t length);
// Logs a string
void Log_string(char *string);
// Logs an integer
void Log_integer(size_t integer);

#endif

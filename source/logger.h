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

void Log_enable();
void Log_disable();
logStatus Log_status();
void Log_data(uint8_t *address, size_t length);
void Log_string(char *string);
void Log_integer(size_t integer);

#endif

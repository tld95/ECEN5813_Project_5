/*
 * PES Project Three display memory header code implementation
 * Tristan Duenas
 * References:
 */

#ifndef __DISPLAY_MEMORY_H__
#define __DISPLAY_MEMORY_H__

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "logger.h"
#include "mem_status.h"

#if defined(FB_RUN) || defined(FB_DEBUG)
#include "fsl_debug_console.h"
#endif

uint8_t* display_memory(uint32_t *loc, size_t length, mem_status *status);

#endif

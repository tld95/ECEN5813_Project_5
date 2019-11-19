/*
 *  PES Project Two/Three Timing Control header code implementation
 *	Tristan Duenas
 *	References: My (Tristan Duenas) PES Project 2 timing_control module
 */

#ifndef __TIMING_CONTROL_H__
#define __TIMING_CONTROL_H__

#include <stdio.h>
#include <stdint.h>

#if defined(FB_RUN) || defined(FB_DEBUG)
#include "clock_config.h"
#endif

#if defined(PC_RUN) || defined(PC_DEBUG)
#include <sys/time.h>
#define CLOCK_DIVISOR 2.0
#endif

#include "MKL25Z4.h"
#include "logger.h"

#define MILLI_SEC_IN_SEC 1000.0

/*
 * The delay function delays for n milliseconds.
 * When building with either the FB_RUN or FB_DEBUG build flags
 * delay will use the KL25Z clock frequency to determine the amount
 * of cycles to wait for n milliseconds.
 * When building with either the PC_RUN or PC_DEBUG build flags
 * delay will use the CLOCKS_PER_SEC from sys/time.h to determine the
 * amount of cycles to wait for n milliseconds.
 */
void delay(volatile uint32_t mSec);
void initSysTick();
void SysTick_Handler();
void getTimeStamp(char* timeStamp);

#endif

/*
 *  PES Project Two LED Control header code implementation
 *	Tristan Duenas
 */

#ifndef __LED_CONTROL_H__
#define __LED_CONTROL_H__

#include <stdio.h>
#include <stdint.h>

#if defined(FB_RUN) || defined(FB_DEBUG)
#include "board.h"
#include "fsl_debug_console.h"
#endif

typedef enum
{
	RED,
	GREEN,
	BLUE
} ledColors;

/*
 * When building with FB_RUN ledOn just turns on the specified color LED for n milliseconds.
 * When building with FB_DEBUG ledOn turns on the specified color LED for n milliseconds, and
 * outputs to the console which LED has been turned on, and the amount of milliseconds the LED
 * will remain on.
 * When building with PC_RUN ledOn outputs the LED color being turned on to the console.
 * When building with PC_DEBUG ledOn outputs the LED color being turned on, the current time stamp,
 * and the amount of milliseconds since the last LED event
 */
void ledOn(uint32_t mSec, ledColors color);

/*
 * When building with FB_RUN ledOff just turns off the specified color LED for n milliseconds.
 * When building with FB_DEBUG ledOff turns off the specified color LED for n milliseconds, and
 * outputs to the console which LED has been turned off, and the amount of milliseconds the LED
 * will remain off.
 * When building with PC_RUN ledOff outputs the LED color being turned off to the console.
 * When building with PC_DEBUG ledOff outputs the LED color being turned off, the current time stamp,
 * and the amount of milliseconds since the last LED event.
 */
void ledOff(uint32_t mSec, ledColors color);

/*
 * getNextLED_ColorState uses a switch case to rotate through the ledColors enum.
 * This helper function, is used to change the LED color after three LED on/off cycles.
 */
ledColors getNextLED_ColorState(ledColors currentColor);

#endif

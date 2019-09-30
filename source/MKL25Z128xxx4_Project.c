/*
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    MKL25Z128xxx4_Project.c
 * @brief   Application entry point.
 */

#include <stdio.h>
#include <stdint.h>
#if defined(FB_RUN) || defined(FB_DEBUG)
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

#define LED3_PORT GPIOD
#define LED3_PIN 1U
#endif

typedef enum
{
	RED,
	GREEN,
	BLUE
} ledColors;

#define NUM_CYCLES 10
#define NUM_LED_ON_OFF_STATES 20
static uint32_t ledTimeCycles[NUM_LED_ON_OFF_STATES] = {
		3000,1000,2000,600,1000,400,1000,200,500,100,500,100,500,100,1000,200,1000,400,2000,600
};

static void delay(volatile uint32_t mSec);
static void ledOn(uint32_t mSec, ledColors color);
static void ledOff(uint32_t mSec, ledColors color);
static void runTimeDelayLoop(ledColors color);
static ledColors getNextLED_ColorState(ledColors currentColor);


/*
 * @brief   Application entry point.
 */
int main(void) {

#if defined(FB_RUN) || defined(FB_DEBUG)
  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    LED_RED_INIT(1);
    LED_GREEN_INIT(1);
    LED_BLUE_INIT(1);
#endif

	ledColors startingColor = RED;

#if defined(FB_DEBUG) || defined(PC_DEBUG)
	PRINTF("Program Start");
#endif
    runTimeDelayLoop(startingColor);
#if defined(FB_DEBUG) || defined(PC_DEBUG)
    PRINTF("Program End");
#endif
    return 0 ;
}

static void runTimeDelayLoop(ledColors color)
{
	uint32_t cycles = 0;
	uint32_t threeCycleCount = 0;
	while (cycles < NUM_CYCLES)
	{
		for (uint32_t index = 0; index < NUM_LED_ON_OFF_STATES; index += 2)
		{
			ledOn(ledTimeCycles[index], BLUE);
			ledOff(ledTimeCycles[index+1], BLUE);
			threeCycleCount++;
			if (threeCycleCount > 2)
			{
				color = getNextLED_ColorState(color);
				threeCycleCount = 0;
			}
		}
		cycles++;
	}
}

static ledColors getNextLED_ColorState(ledColors currentColor)
{
	ledColors nextColor = RED;
	switch (currentColor)
	{
		case RED:
			nextColor = GREEN;
			break;
		case GREEN:
			nextColor = BLUE;
			break;
		case BLUE:
			nextColor = RED;
			break;
		default:
			// Do nothing
			break;
	}
	return nextColor;
}

static void ledOn(uint32_t mSec, ledColors color)
{
	switch (color)
	{
		case RED:
#if defined(FB_RUN) || defined(FB_DEBUG)
			LED_RED_ON();
#endif
#ifdef FB_DEBUG
			PRINTF("LED RED ON %d\n", mSec);
#endif
			break;
		case GREEN:
#if defined(FB_RUN) || defined(FB_DEBUG)
			LED_GREEN_ON();
#endif
#ifdef FB_DEBUG
			PRINTF("LED GREEN ON %d\n", mSec);
#endif
			break;
		case BLUE:
#if defined(FB_RUN) || defined(FB_DEBUG)
			LED_BLUE_ON();
#endif
#ifdef FB_DEBUG
			PRINTF("LED BLUE ON %d\n", mSec);
#endif
			break;
		default:
			// Do nothing
			break;
	}
	delay(mSec);
}

static void ledOff(uint32_t mSec, ledColors color)
{
	switch (color)
	{
		case RED:
#if defined(FB_RUN) || defined(FB_DEBUG)
			LED_RED_OFF();
#endif
#ifdef FB_DEBUG
			PRINTF("LED RED OFF %d\n", mSec);
#endif
			break;
		case GREEN:
#if defined(FB_RUN) || defined(FB_DEBUG)
			LED_GREEN_OFF();
#endif
#ifdef FB_DEBUG
			PRINTF("LED GREEN OFF %d\n", mSec);
#endif
			break;
		case BLUE:
#if defined(FB_RUN) || defined(FB_DEBUG)
			LED_BLUE_OFF();
#endif
#ifdef	FB_DEBUG
			PRINTF("LED BLUE OFF %d\n", mSec);
#endif
			break;
		default:
			// Do nothing
			break;
	}
	delay(mSec);
}

static void delay(volatile uint32_t mSec)
{
	uint32_t cyclesPerMsec = 0;
#if defined(FB_RUN) || defined(FB_DEBUG)
	cyclesPerMsec = oscConfig_BOARD_BootClockRUN.freq / 1000;
#endif

//TODO put cpu clock in
#if defined(PC_RUN) || defined(PC_DEBUG)
	cyclesPerMsec = 0 / 1000;
#endif

	uint32_t delayCycles = mSec * cyclesPerMsec;
	while(delayCycles!=0)
	{
		__asm volatile("NOP");
		delayCycles--;
	}
}

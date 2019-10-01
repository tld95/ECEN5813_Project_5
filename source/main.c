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
 
/*
 * PES Project Two main source code implementation
 * Tristan Duenas
 * References:
 * https://stackoverflow.com/questions/15436060/how-to-get-timestamp-in-c
 */

/*
 * BUILD FLAGS
 * FB_RUN - For running on board with LED output without console output
 * FB_DEBUG - For running on board with LED output with console output
 * PC_RUN - For running on local PC without LED output with console output (no time stamps)
 * PC_DEBUG For running on local PC without LED output with console output (with time stamps)
 */

// LED/Timing Project 2 C modules
#include "LED_control.h"
#include "timing_control.h"

// KL25Z hardware includes/defines
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

#define NUM_CYCLES 10
#define NUM_LED_ON_OFF_STATES 20
static uint32_t ledTimeCycles[NUM_LED_ON_OFF_STATES] = {
		3000,1000,2000,600,1000,400,1000,200,500,100,500,100,500,100,1000,200,1000,400,2000,600
};

static void runTimeDelayLoop(ledColors color);

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

#ifdef FB_DEBUG
	PRINTF("Program Start\n");
#endif
#ifdef PC_DEBUG
	printf("Program Start\n");
#endif
    runTimeDelayLoop(startingColor);
#ifdef FB_DEBUG
    PRINTF("Program End\n");
#endif
#ifdef PC_DEBUG
    printf("Program End\n");
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
			ledOn(ledTimeCycles[index], color);
			ledOff(ledTimeCycles[index+1], color);
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

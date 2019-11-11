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
 * PES Project Four main source code implementation
 * Tristan Duenas
 * References:
 * PES Project 4
 */

/*
 * BUILD FLAGS
 * FB_RUN - For running on board with LED output without console output
 * FB_DEBUG - For running on board with LED output with console output
 * PC_RUN - For running on local PC without LED output with console output (no time stamps)
 * PC_DEBUG For running on local PC without LED output with console output (with time stamps)
 */

#include <color_sensor_control.h>
#include <stddef.h>

// Project 4 C modules
#include "logger.h"
#include "led_control.h"
#include "timing_control.h"
#include "i2c_control.h"
#include "state_machines.h"
#include "project_4_tests.h"

// KL25Z hardware includes/defines
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"


#define LED3_PORT GPIOD
#define LED3_PIN 1U

void i2c_init();
void i2c_write_byte(uint8_t dev, uint8_t reg, uint8_t data);
uint8_t i2c_read_byte(uint8_t dev, uint8_t reg);

int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    LED_RED_INIT(1);
    LED_GREEN_INIT(1);
    LED_BLUE_INIT(1);

    led_control(OFF);

    Log_enable();

	color_sensor_init();

#ifdef TEST_FLAG
    runProject4Tests();
#endif

	uint8_t postTestPassed = 0;
    while (true)
    {
		if (postTestPassed == 0)
		{
			status sensorStatus = color_sensor_POST_Test();
			if (sensorStatus == FAILED)
			{
				led_control(RED);
				Log_string(STATUS_LEVEL, MAIN, "POST Test Failed.");
			}
			else
			{
				Log_string(STATUS_LEVEL, MAIN, "POST Test Passed.");
				postTestPassed = 1;
			}
		}
		else
		{
			run_state_machines();
		}
		delay(100);
    }
    return 0 ;
}

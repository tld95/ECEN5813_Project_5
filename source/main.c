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

#include <project_5_tests.h>
#include <stddef.h>

// Project 4 C modules
#include "logger.h"
#include "led_control.h"
#include "timing_control.h"
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "uart0_control.h"
#include "circular_buffer.h"
#include "application.h"

#define LED3_PORT GPIOD
#define LED3_PIN 1U

int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    initSysTick();

    LED_RED_INIT(1);
    LED_GREEN_INIT(1);
    LED_BLUE_INIT(1);

    uart0_Init(115200, NONE);

#ifdef APPLICATION_MODE
    applicationInit();
#endif

    led_control(OFF);

    Log_enable();

#ifdef TEST_FLAG
    runProject5Tests();
#endif

    while (1)
    {
#ifdef ECHO_MODE
#ifdef UART_POLLING_DRIVEN
    	uart0_PollingEchoCharacter();
#endif
#ifdef UART_INTERRUPT_DRIVEN
    	uart0_InterruptEchoCharacter();
#endif
#endif

#ifdef APPLICATION_MODE
    	processAndDisplayReceivedCharacters();
#endif
    }

    return 0 ;
}

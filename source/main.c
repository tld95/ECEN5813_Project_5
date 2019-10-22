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
 * PES Project Three main source code implementation
 * Tristan Duenas
 * References:
 * PES Project 3 (1.5)
 */

/*
 * BUILD FLAGS
 * FB_RUN - For running on board with LED output without console output
 * FB_DEBUG - For running on board with LED output with console output
 * PC_RUN - For running on local PC without LED output with console output (no time stamps)
 * PC_DEBUG For running on local PC without LED output with console output (with time stamps)
 */

#include <stddef.h>

// Project 3 C modules
#include "allocate_words.h"
#include "free_words.h"
#include "display_memory.h"
#include "write_memory.h"
#include "invert_block.h"
#include "write_pattern.h"
#include "verify_pattern.h"
#include "logger.h"
#include "led_control.h"
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

#define SIXTEEN 16
#define SIXTEEN_BYTES 16
#define SIXTY_FOUR_BYTES 64
#define SEED 255

void setLED_RedOnError(mem_status state);

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

	Log_enable();
	Log_string("Program Started.");
	Log_string("");
	led_control(OFF);
	delay(1000);

	uint32_t* memory_block = NULL;
	uint8_t* bytePointer = NULL;
	uint32_t* miscompareListPointer = NULL;
	mem_status status = SUCCESS;
	mem_status tempStatus = SUCCESS;

	// Referenced comments from PES Project 3 (1.5)

	// Allocate 16 bytes
	led_control(BLUE);
	memory_block = allocate_words(SIXTEEN_BYTES);
	Log_string("");
	delay(1000);

	// Write a memory pattern to the allocated 16 byte region using a selected seed
	status |= write_pattern(memory_block, SIXTEEN_BYTES, SEED);
	setLED_RedOnError(status);
	// Display that region’s memory pattern
	bytePointer = display_memory(memory_block, SIXTEEN_BYTES, &tempStatus);
	status |= tempStatus;
	setLED_RedOnError(status);
	// Verify that region’s memory pattern (should pass)
	miscompareListPointer = verify_pattern(memory_block, SIXTEEN_BYTES, SEED, &tempStatus);
	status |= tempStatus;
	setLED_RedOnError(status);
	free_words((uint32_t*)bytePointer);
	free_words(miscompareListPointer);
	Log_string("");
	delay(1000);

	//Write 0xFFEE to a position within that region (location + some offset you select)
	uint16_t value = 0xFFEE;
	memcpy(memory_block + 1, &value, sizeof(uint16_t));
	// Display that region’s memory pattern
	bytePointer = display_memory(memory_block, SIXTEEN_BYTES, &tempStatus);
	status |= tempStatus;
	setLED_RedOnError(status);
	// Verify the memory pattern again (should error)
	miscompareListPointer = verify_pattern(memory_block, SIXTEEN_BYTES, SEED, &tempStatus);
	status |= tempStatus;
	setLED_RedOnError(status);
	free_words((uint32_t*)bytePointer);
	free_words(miscompareListPointer);
	Log_string("");
	delay(1000);

	// Write a memory pattern to the region using the same seed as before
	status |= write_pattern(memory_block, SIXTEEN_BYTES, SEED);
	setLED_RedOnError(status);
	// Display that region’s memory pattern
	bytePointer = display_memory(memory_block, SIXTEEN_BYTES, &tempStatus);
	status |= tempStatus;
	setLED_RedOnError(status);
	// Verify that memory pattern again (should pass)
	miscompareListPointer = verify_pattern(memory_block, SIXTEEN_BYTES, SEED, &tempStatus);
	status |= tempStatus;
	setLED_RedOnError(status);
	free_words((uint32_t*)bytePointer);
	free_words(miscompareListPointer);
	Log_string("");
	delay(1000);

	// Invert 4 bytes in the region (location + some offset)
	status |= invert_block(memory_block+1, 4);
	setLED_RedOnError(status);
	// Display that region’s memory pattern
	bytePointer = display_memory(memory_block, SIXTEEN_BYTES, &tempStatus);
	status |= tempStatus;
	setLED_RedOnError(status);
	// Verify the memory pattern again (should error)
	miscompareListPointer = verify_pattern(memory_block, SIXTEEN_BYTES, SEED, &tempStatus);
	status |= tempStatus;
	setLED_RedOnError(status);
	free_words((uint32_t*)bytePointer);
	free_words(miscompareListPointer);
	Log_string("");
	delay(1000);

	// Invert those 4 bytes again in the LMA region (location + some offset)
	status |= invert_block(memory_block+1, 4);
	setLED_RedOnError(status);
	// Display that region’s memory pattern
	bytePointer = display_memory(memory_block, SIXTEEN_BYTES, &tempStatus);
	status |= tempStatus;
	setLED_RedOnError(status);
	// Verify that memory pattern again (should pass)
	miscompareListPointer = verify_pattern(memory_block, SIXTEEN_BYTES, SEED, &tempStatus);
	status |= tempStatus;
	setLED_RedOnError(status);
	free_words((uint32_t*)bytePointer);
	free_words(miscompareListPointer);
	Log_string("");
	delay(1000);

	if (status == SUCCESS)
	{
		led_control(GREEN);
	}

	// Free the 16 byte allocated region (if necessary on your target)
	free_words(memory_block);
	Log_string("Program Ended.");
	Log_disable();
    return 0 ;
}

void setLED_RedOnError(mem_status state)
{
	if (state == FAILED)
	{
		led_control(RED);
	}
}

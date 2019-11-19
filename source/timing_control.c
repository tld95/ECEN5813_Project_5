/*
 * PES Project Two Timing Control source code implementation
 * Tristan Duenas
 * Referenced:
 * PES Coding Exercise.pdf
 */

#include "timing_control.h"

uint32_t time = 0;

void delay(volatile uint32_t mSec)
{
#if defined(FB_RUN) || defined(FB_DEBUG)
	uint32_t cyclesPerMsec = oscConfig_BOARD_BootClockRUN.freq / MILLI_SEC_IN_SEC;

	uint32_t delayCycles = mSec * cyclesPerMsec;
	while(delayCycles!=0)
	{
		__asm volatile("NOP");
		delayCycles--;
	}
#endif

#if defined(PC_RUN) || defined(PC_DEBUG)
	uint64_t cyclesPerMsec = (CLOCKS_PER_SEC * MILLI_SEC_IN_SEC)/CLOCK_DIVISOR;
	uint64_t delayCycles = mSec * cyclesPerMsec;
	while(delayCycles!=0)
	{
		delayCycles--;
	}
#endif
}

void initSysTick()
{
	// Referenced PES Coding Exercise.pdf
	SysTick->LOAD = (oscConfig_BOARD_BootClockRUN.freq / MILLI_SEC_IN_SEC);
	NVIC_SetPriority(SysTick_IRQn, 3);
	SysTick->VAL = 0;
	SysTick->CTRL = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
	NVIC_EnableIRQ(SysTick_IRQn);
}

void SysTick_Handler()
{
	time++;
}

void getTimeStamp(char* timeStamp)
{
	uint32_t hours = time / 3600000L;
	uint32_t minutes = (time - (hours * 3600000)) / 60000L;
	uint32_t seconds = (time - (hours * 3600000) - (minutes * 60000)) / 1000;
	uint32_t n = (time - (hours * 3600000) - (minutes * 60000) - (seconds * 1000));

	// Referenced https://www.geeksforgeeks.org/snprintf-c-library/
	char buf[15];
	snprintf(buf, 15, "%d:%d:%d:%d", hours, minutes, seconds, n);
	strcpy(timeStamp, buf);
}

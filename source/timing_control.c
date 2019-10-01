/*
 * PES Project Two Timing Control source code implementation
 * Tristan Duenas
 */

#include "timing_control.h"

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

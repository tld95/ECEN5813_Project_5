/*
 * PES Project Two LED Control source code implementation
 * Tristan Duenas
 * References:
 * https://stackoverflow.com/questions/15436060/how-to-get-timestamp-in-c
 */

#include "LED_control.h"
#include "timing_control.h"

ledColors getNextLED_ColorState(ledColors currentColor)
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

void ledOn(uint32_t mSec, ledColors color)
{
#ifdef PC_DEBUG
	time_t rawTime;
	struct tm *timeInfo;
	char buffer[16];
#endif

	switch (color)
	{
		case RED:
#if defined(FB_RUN) || defined(FB_DEBUG)
			LED_RED_ON();
#endif
#ifdef FB_DEBUG
			PRINTF("LED RED ON %d\n", mSec);
#endif
#ifdef PC_RUN
			printf("LED RED ON\n");
			fflush(stdout);
#endif
#ifdef PC_DEBUG
			// Referenced https://stackoverflow.com/questions/15436060/how-to-get-timestamp-in-c
			time(&rawTime);
			timeInfo = localtime(&rawTime);
			strftime(buffer,16,"%H:%M:%S",timeInfo);
			printf("LED RED ON %s %d\n", buffer, (int)mSec);
			fflush(stdout);
#endif
			break;
		case GREEN:
#if defined(FB_RUN) || defined(FB_DEBUG)
			LED_GREEN_ON();
#endif
#ifdef FB_DEBUG
			PRINTF("LED GREEN ON %d\n", mSec);
#endif
#ifdef PC_RUN
			printf("LED GREEN ON\n");
			fflush(stdout);
#endif
#ifdef PC_DEBUG
			// Referenced https://stackoverflow.com/questions/15436060/how-to-get-timestamp-in-c
			time(&rawTime);
			timeInfo = localtime(&rawTime);
			strftime(buffer,16,"%H:%M:%S",timeInfo);
			printf("LED GREEN ON %s %d\n", buffer, (int)mSec);
			fflush(stdout);
#endif
			break;
		case BLUE:
#if defined(FB_RUN) || defined(FB_DEBUG)
			LED_BLUE_ON();
#endif
#ifdef FB_DEBUG
			PRINTF("LED BLUE ON %d\n", mSec);
#endif
#ifdef PC_RUN
			printf("LED BLUE ON\n");
			fflush(stdout);
#endif
#ifdef PC_DEBUG
			// Referenced https://stackoverflow.com/questions/15436060/how-to-get-timestamp-in-c
			time(&rawTime);
			timeInfo = localtime(&rawTime);
			strftime(buffer,16,"%H:%M:%S",timeInfo);
			printf("LED BLUE ON %s %d\n", buffer, (int)mSec);
			fflush(stdout);
#endif
			break;
		default:
			// Do nothing
			break;
	}
	delay(mSec);
}

void ledOff(uint32_t mSec, ledColors color)
{
#ifdef PC_DEBUG
	time_t rawTime;
	struct tm *timeInfo;
	char buffer[16];
#endif

	switch (color)
	{
		case RED:
#if defined(FB_RUN) || defined(FB_DEBUG)
			LED_RED_OFF();
#endif
#ifdef FB_DEBUG
			PRINTF("LED RED OFF %d\n", mSec);
#endif
#ifdef PC_RUN
			printf("LED RED OFF\n");
			fflush(stdout);
#endif
#ifdef PC_DEBUG
			// Referenced https://stackoverflow.com/questions/15436060/how-to-get-timestamp-in-c
			time(&rawTime);
			timeInfo = localtime(&rawTime);
			strftime(buffer,16,"%H:%M:%S",timeInfo);
			printf("LED RED OFF %s %d\n", buffer, (int)mSec);
			fflush(stdout);
#endif
			break;
		case GREEN:
#if defined(FB_RUN) || defined(FB_DEBUG)
			LED_GREEN_OFF();
#endif
#ifdef FB_DEBUG
			PRINTF("LED GREEN OFF %d\n", mSec);
#endif
#ifdef PC_RUN
			printf("LED GREEN OFF\n");
			fflush(stdout);
#endif
#ifdef PC_DEBUG
			// Referenced https://stackoverflow.com/questions/15436060/how-to-get-timestamp-in-c
			time(&rawTime);
			timeInfo = localtime(&rawTime);
			strftime(buffer,16,"%H:%M:%S",timeInfo);
			printf("LED GREEN OFF %s %d\n", buffer, (int)mSec);
			fflush(stdout);
#endif
			break;
		case BLUE:
#if defined(FB_RUN) || defined(FB_DEBUG)
			LED_BLUE_OFF();
#endif
#ifdef	FB_DEBUG
			PRINTF("LED BLUE OFF %d\n", mSec);
#endif
#ifdef PC_RUN
			printf("LED BLUE OFF\n");
			fflush(stdout);
#endif
#ifdef PC_DEBUG
			// Referenced https://stackoverflow.com/questions/15436060/how-to-get-timestamp-in-c
			time(&rawTime);
			timeInfo = localtime(&rawTime);
			strftime(buffer,16,"%H:%M:%S",timeInfo);
			printf("LED BLUE OFF %s %d\n", buffer, (int)mSec);
			fflush(stdout);
#endif
			break;
		default:
			// Do nothing
			break;
	}
	delay(mSec);
}

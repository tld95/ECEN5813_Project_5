/*
 * PES Project Three display logger source code implementation
 * Tristan Duenas
 * References:
 * https://stackoverflow.com/questions/16370673/how-to-print-32-bit-value-complete
 */

#include "logger.h"

static uint8_t logEnabled = 0;

void Log_enable()
{
	logEnabled = ENABLED;
}

void Log_disable()
{
	logEnabled = DISABLED;
}

logStatus Log_status()
{
	return logEnabled;
}

void Log_data(uint8_t *address, size_t length)
{
	if (Log_status() == ENABLED)
	{
		// Referenced https://stackoverflow.com/questions/16370673/how-to-print-32-bit-value-complete
		#ifdef FB_DEBUG
			PRINTF("Address: 0x%08X ", (uint32_t*)address);
		#endif
		#ifdef PC_DEBUG
			printf("Address: 0x%08X ", (uint32_t*)address);
			fflush(stdout);
		#endif

		#ifdef FB_DEBUG
			PRINTF("Value: 0x");
		#endif
		#ifdef PC_DEBUG
			printf("Value: 0x");
			fflush(stdout);
		#endif

		for (uint32_t index = 0; index < length; index++)
		{
			#ifdef FB_DEBUG
				PRINTF("%02X", address[index]);
			#endif
			#ifdef PC_DEBUG
				printf("%02X", address[index]);
				fflush(stdout);
			#endif
		}

		#ifdef FB_DEBUG
			PRINTF("\n");
		#endif
		#ifdef PC_DEBUG
			printf("\n");
			fflush(stdout);
		#endif
	}
}

void Log_string(char *string)
{
	if (Log_status() == ENABLED)
	{
		#ifdef FB_DEBUG
			PRINTF("%s\r\n", string);
		#endif
		#ifdef PC_DEBUG
			printf("%s\n", string);
			fflush(stdout);
		#endif
	}
}

void Log_integer(size_t integer)
{
	if (Log_status() == ENABLED)
	{
		#ifdef FB_DEBUG
			PRINTF("%d\r\n", integer);
		#endif
		#ifdef PC_DEBUG
			printf("%d\n", integer);
			fflush(stdout);
		#endif
	}
}

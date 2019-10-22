/*
 * PES Project Three verify pattern source code implementation
 * Tristan Duenas
 * References:
 */

#include "verify_pattern.h"

uint32_t* verify_pattern(uint32_t *loc, size_t length, int8_t seed, mem_status* status)
{
	uint8_t *pattern = generate_pattern(length, seed);
	uint32_t *byteAddressMiscompareList = (uint32_t*)malloc(sizeof(uint32_t) * length);
	memset(byteAddressMiscompareList, 0, sizeof(uint32_t) * length);
	uint32_t miscompareIndex = 0;
	uint8_t *dataEightBit = (uint8_t*)loc;

	Log_string("Pattern Generated to Verify:");
	Log_data(pattern, length);

	for (uint32_t index = 0; index < length; index++)
	{
		if (dataEightBit[index] != pattern[index])
		{
			byteAddressMiscompareList[miscompareIndex] = (uint32_t)&dataEightBit[index];
			miscompareIndex++;
		}
	}

	if (miscompareIndex == 0)
	{
		*status = SUCCESS;
		Log_string("Verify Pattern Succeeded");
	}
	else
	{
		*status = FAILED;
		Log_string("Verify Pattern Failed");
		Log_string("Addresses Failed At:");
		for (uint32_t index = 0; index < miscompareIndex; index++)
		{
			Log_data((uint8_t*)byteAddressMiscompareList[index], 1);
		}
	}

	free_words((uint32_t*)pattern);
	return byteAddressMiscompareList;
}

/*
 * PES Project Three display invert block source code implementation
 * Tristan Duenas
 * References:
 */

#include "invert_block.h"

mem_status invert_block(uint32_t *loc, size_t length)
{
	uint8_t *bytePointer = (uint8_t*)loc;
	if (loc == NULL)
	{
		return FAILED;
	}
	else
	{
		Log_string("Inverting Memory Block.");
		for (uint32_t index = 0; index < length; index++)
		{
			bytePointer[index] ^= 0xFF;
		}
	}
	return SUCCESS;
}

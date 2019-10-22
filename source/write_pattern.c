/*
 * PES Project Three write pattern source code implementation
 * Tristan Duenas
 * References:
 */

#include "write_pattern.h"

mem_status write_pattern(uint32_t *loc, size_t length, int8_t seed)
{
	uint8_t *pattern = generate_pattern(length, seed);
	uint8_t *bytePointer = (uint8_t*)loc;

	for (uint32_t index = 0; index < length; index++)
	{
		uint32_t* address = (uint32_t*)(&bytePointer[index]);
		write_memory(address, pattern[index]);
	}

	Log_string("Pattern Written to Memory.");

	free_words((uint32_t*)pattern);
	return SUCCESS;
}

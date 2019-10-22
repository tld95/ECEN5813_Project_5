/*
 * PES Project Three allocate words source code implementation
 * Tristan Duenas
 * References:
 */

#include "allocate_words.h"

uint32_t *allocate_words(size_t length)
{
	uint32_t *allocatedMemory = NULL;
	if (length < MAX_MEMORY_ALLOCATION_SIZE)
	{
		allocatedMemory = (uint32_t *)malloc(length);
	}
	if (allocatedMemory != NULL)
	{
		Log_string("Memory Block Allocated Successfully.");
	}
	else
	{
		Log_string("Memory Block Allocation Failed.");
	}
	return allocatedMemory;
}

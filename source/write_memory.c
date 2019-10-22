/*
 * PES Project Three write memory source code implementation
 * Tristan Duenas
 * References:
 */

#include "write_memory.h"

mem_status write_memory(uint32_t *loc, uint8_t value)
{
	if (loc == NULL)
	{
		return FAILED;
	}
	else
	{
		*(uint8_t*)loc = value;
	}
	return SUCCESS;
}

/*
 * PES Project Three display memory source code implementation
 * Tristan Duenas
 * References:
 */

#include "display_memory.h"

uint8_t* display_memory(uint32_t *loc, size_t length, mem_status* status)
{
	uint8_t *data = malloc(sizeof(uint8_t) * length);
	if (data != NULL)
	{
		memcpy(data, loc, length);
		Log_string("Displaying Memory:");
		Log_data((uint8_t*)loc, length);
		*status = SUCCESS;
	}
	else
	{
		*status = FAILED;
	}
	return data;
}

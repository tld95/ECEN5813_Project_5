/*
 * PES Project Three gen pattern source code implementation
 * Tristan Duenas
 * References:
 */

#include "gen_pattern.h"

uint8_t* generate_pattern(size_t length, int8_t seed)
{
	uint8_t *patternGenerated = (uint8_t*)malloc(sizeof(uint8_t) * length);
	memset(patternGenerated, 0, sizeof(uint8_t) * length);

	for (uint32_t index = 0; index < length; index++)
	{
		patternGenerated[index] ^= seed;
	}

	return patternGenerated;
}

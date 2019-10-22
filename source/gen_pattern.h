/*
 * PES Project Three gen pattern header code implementation
 * Tristan Duenas
 * References:
 */

#ifndef __GEN_PATTERN_H__
#define __GEN_PATTERN_H__

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// Takes a seed and XORs each byte memory block provided with that seed to create a deterministic pseudo random pattern.
uint8_t* generate_pattern(size_t length, int8_t seed);

#endif

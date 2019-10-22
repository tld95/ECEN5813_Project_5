/*
 * PES Project Three write pattern header code implementation
 * Tristan Duenas
 * References:
 */

#ifndef __WRITE_PATTERN_H__
#define __WRITE_PATTERN_H__

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "write_memory.h"
#include "gen_pattern.h"
#include "free_words.h"
#include "logger.h"

// Writes a generated pattern based on a seed to a block of memory.
mem_status write_pattern(uint32_t *loc, size_t length, int8_t seed);

#endif

/*
 * PES Project Three verify pattern header code implementation
 * Tristan Duenas
 * References:
 */

#ifndef __VERIFY_PATTERN_H__
#define __VERIFY_PATTERN_H__

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "gen_pattern.h"
#include "free_words.h"
#include "mem_status.h"
#include "logger.h"

#define SIXTEEN_BYTES 16

uint32_t* verify_pattern(uint32_t *loc, size_t length, int8_t seed, mem_status* status);

#endif

/*
 * PES Project Three write memory header code implementation
 * Tristan Duenas
 * References:
 */

#ifndef __WRITE_MEMORY_H__
#define __WRITE_MEMORY_H__

#include <stdint.h>
#include <stddef.h>
#include "mem_status.h"

// Writes 8 bit value to memory location
mem_status write_memory(uint32_t *loc, uint8_t value);
// Write 16 bit value to memory location
mem_status write_memory_16_bit_value(uint32_t *loc, uint16_t value);

#endif

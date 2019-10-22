/*
 * PES Project Three display invert block header code implementation
 * Tristan Duenas
 * References:
 */

#ifndef __INVERT_BLOCK_H__
#define __INVERT_BLOCK_H__

#include <stdint.h>
#include <stddef.h>
#include "mem_status.h"
#include "logger.h"

// Takes a block of memory and inverts a designated amount of bytes by XORing with 0xFF.
mem_status invert_block(uint32_t *loc, size_t length);

#endif

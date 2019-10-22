/*
 * PES Project Three allocate words header code implementation
 * Tristan Duenas
 * References:
 */

#ifndef __ALLOCATE_WORDS_H__
#define __ALLOCATE_WORDS_H__

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "logger.h"

#define MAX_MEMORY_ALLOCATION_SIZE 100

// Allocates block of memory using malloc
uint32_t *allocate_words(size_t length);

#endif

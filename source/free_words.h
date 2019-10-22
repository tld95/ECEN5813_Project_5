/*
 * PES Project Three free words header code implementation
 * Tristan Duenas
 * References:
 */

#ifndef __FREE_WORDS_H__
#define __FREE_WORDS_H__

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#if defined(FB_RUN) || defined(FB_DEBUG)
#include "fsl_debug_console.h"
#endif

// Frees block of memory
void free_words(uint32_t* src);

#endif

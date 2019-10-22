/*
 * PES Project Three get address header code implementation
 * Tristan Duenas
 * References:
 */

#ifndef __GET_ADDRESS_H__
#define __GET_ADDRESS_H__

#include <stdint.h>
#include <stdlib.h>

// Takes a base address and offset, and returns a new address with the combined base address and offset.
uint32_t* get_address(uint32_t *baseAddress, uint32_t offset);

#endif

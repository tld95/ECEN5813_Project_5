/*
 * PES Project Four I2C Control header code implementation
 * Tristan Duenas
 * References:
 * https://canvas.colorado.edu/courses/53078/files/folder/unfiled?preview=9315870
 * PES I2C Polling Dean File
 */

#ifndef __I2C_CONTROL_H__
#define __I2C_CONTROL_H__

#include "clock_config.h"
#include "MKL25Z4.h"
#include "logger.h"

// Referencing PES I2C Polling Dean File
#define I2C_M_START I2C1->C1 |= I2C_C1_MST_MASK
#define I2C_M_STOP I2C1->C1 &= ~I2C_C1_MST_MASK
#define I2C_M_RSTART I2C1->C1 |= I2C_C1_RSTA_MASK
#define I2C_TRAN I2C1->C1 |= I2C_C1_TX_MASK
#define ACK I2C1->C1 &= ~I2C_C1_TXAK_MASK
#define I2C_REC I2C1->C1 &= ~I2C_C1_TX_MASK
#define NACK I2C1->C1 |= I2C_C1_TXAK_MASK

#define MILLI_SEC_IN_SEC 1000.0

typedef enum status
{
	PASSED,
	FAILED
} status;

status i2c_wait(uint8_t mask, uint8_t shift, uint8_t state);
status i2c_transmit(uint8_t data, uint8_t start, uint8_t restart);

#endif

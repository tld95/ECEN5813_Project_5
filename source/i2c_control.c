/*
 * PES Project Four I2C Control source code implementation
 * Tristan Duenas
 * References:
 */

#include "i2c_control.h"

status i2c_wait(uint8_t mask, uint8_t shift, uint8_t state)
{
	// Timeout after 50ms
	uint32_t cyclesPerMsec = oscConfig_BOARD_BootClockRUN.freq / MILLI_SEC_IN_SEC;
	uint32_t delayCycles = 50 * cyclesPerMsec;
	uint32_t count = 0;
	uint8_t goodState = (((I2C1->S & mask) >> shift) == state);
	while((goodState == 0) && count < delayCycles)
	{
		goodState = (((I2C1->S & mask) >> shift) == state);
		count++;
	}
	if (count < delayCycles)
	{
		return PASSED;
	}
	else
	{
		return FAILED;
	}
}

status i2c_transmit(uint8_t data, uint8_t start, uint8_t restart)
{
	if (start == 1)
	{
		// Make sure line isn't busy
		if (i2c_wait(I2C_S_BUSY_MASK, I2C_S_BUSY_SHIFT, 0) == FAILED)
		{
			I2C_M_STOP;
			delay(50);
			I2C1->S = 0xFF;
			delay(50);
			return FAILED;
		}
		I2C_TRAN;
		I2C_M_START;
	}
	if (restart == 1)
	{
		I2C_M_START;
	}
	// Transmit slave address
	I2C1->D = data;
	if (i2c_wait(I2C_S_IICIF_MASK, I2C_S_IICIF_SHIFT, 1) == FAILED)
	{
		I2C1->S = 0xFF;
		I2C_M_STOP;
		return FAILED;
	}
	else
	{
		// Clear IICIF bit in status register
		I2C1->S |= I2C_S_IICIF_MASK;
	}

	// Check for arbitration
	if ((I2C1->S & I2C_S_ARBL_MASK) != 0)
	{
		// Clear arbitration
		I2C1->S |= I2C_S_ARBL_MASK;
	}
	else
	{
		// Check for acknowledgment from slave
		if ((i2c_wait(I2C_S_RXAK_MASK, I2C_S_RXAK_SHIFT, 1) == FAILED)
				&& (i2c_wait(I2C_S_IAAS_MASK, I2C_S_IAAS_SHIFT, 1) == FAILED))
		{
			I2C1->S = 0xFF;
			I2C_M_STOP;
			return FAILED;
		}
	}
	return PASSED;
}

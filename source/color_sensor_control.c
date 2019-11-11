/*
 * PES Project Four TCS3472 Color Sensor Control source code implementation
 * Tristan Duenas
 * References: PES I2C Polling Dean.docx
 */

#include "color_sensor_control.h"
#include "logger.h"

static uint8_t gAddr = 0;

void color_sensor_init(uint8_t addr)
{

	// Referenced PES I2C Polling Dean.docx
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	SIM->SCGC4 |= SIM_SCGC4_I2C1_MASK;
    I2C1->F = I2C_F_ICR(0x11) | I2C_F_MULT(1);
	I2C1->C1 |= I2C_C1_IICEN_MASK;
	I2C1->C1 |= I2C_C2_HDRS_MASK;
	I2C1->A1 = addr << 1;
	gAddr = addr;


	status tempStatus = FAILED;
	while (tempStatus != PASSED)
	{
		// Command color sensor power on
		tempStatus = i2c_transmit(I2C1->A1, 1, 0);
		if (tempStatus == FAILED)
		{
			continue;
		}
		tempStatus = i2c_transmit(0x80, 0, 0);
		if (tempStatus == FAILED)
		{
			continue;
		}
		tempStatus = i2c_transmit(0x01, 0, 0);
		if (tempStatus == FAILED)
		{
			continue;
		}
		I2C_M_STOP;

		// At least 2.4 ms must pass after power on before RGBC can be initialized
		delay(10);

		// Command color sensor AEN RGBC enable
		tempStatus = i2c_transmit(0x52, 1, 0);
		if (tempStatus == FAILED)
		{
			continue;
		}
		tempStatus = i2c_transmit(0x80, 0, 0);
		if (tempStatus == FAILED)
		{
			continue;
		}
		tempStatus = i2c_transmit(0x03, 0, 0);
		if (tempStatus == FAILED)
		{
			continue;
		}
		I2C_M_STOP;
	}
}

status color_sensor_POST_Test(uint8_t reg)
{
	status tempStatus = PASSED;
	getRegValue(&tempStatus, reg);
	return tempStatus;
}

uint8_t getRegValue(status* tempStatus, uint8_t reg)
{
	volatile uint8_t dummy = 0;
	volatile uint8_t data = 0;
	uint8_t no_device = 0;
	// Transmit slave address with write bit and pointer register location
	if (i2c_transmit(I2C1->A1, 1, 0) == FAILED)
	{
		no_device = 1;
	}
	else
	{
		if (i2c_transmit(reg, 0, 0) == FAILED)
		{
			no_device = 1;
		}
		else
		{
			I2C_M_RSTART;
			// Transmit slave address with read bit only
			if (i2c_transmit((0x53), 0, 0) == FAILED)
			{
				no_device = 1;
			}
			else
			{
				I2C_REC;
				dummy = I2C1->D;
				ACK;
				delay(10);
				data = I2C1->D;
				ACK;
				delay(10);
				Log_string("Dummy Read:");
				Log_integer(dummy);
				Log_string("Data:");
				Log_integer(data);
				I2C_M_STOP;
			}
		}
	}

	if (no_device == 1)
	{
		*tempStatus = FAILED;
	}
	else
	{
		*tempStatus = PASSED;
	}
	return data;
}
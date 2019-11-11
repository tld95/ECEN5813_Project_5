/*
 * PES Project Four TCS3472 Color Sensor Control header code implementation
 * Tristan Duenas
 * References:
 */

#ifndef __COLOR_SENSOR_H__
#define __COLOR_SENSOR_H__

#include "clock_config.h"
#include "MKL25Z4.h"
#include "i2c_control.h"
#include "timing_control.h"

#define CLEAR_ADC_LOW (0x14 | 0x80)
#define CLEAR_ADC_HIGH (0x15 | 0x80)
#define RED_REGISTER_LOW (0x16 | 0x80)
#define RED_REGISTER_HIGH (0x17 | 0x80)
#define GREEN_REGISTER_LOW (0x18 | 0x80)
#define GREEN_REGISTER_HIGH (0x19 | 0x80)
#define BLUE_REGISTER_LOW (0x1A | 0x80)
#define BLUE_REGISTER_HIGH (0x1B | 0x80)

void color_sensor_init(uint8_t addr);
status color_sensor_POST_Test(uint8_t reg);
uint8_t getRegValue(status* tempStatus, uint8_t reg);

#endif

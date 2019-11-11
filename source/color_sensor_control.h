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
#include "led_control.h"

#define DEVICE_ID (0x44)
#define DEVICE_ADDR (0x29)
#define WRITE_ADDR (0x52)
#define READ_ADDR (0x53)
#define DEVICE_ID_REGISTER (0x12 | 0x80)
#define RED_REGISTER_LOW (0x16 | 0x80)
#define RED_REGISTER_HIGH (0x17 | 0x80)
#define GREEN_REGISTER_LOW (0x18 | 0x80)
#define GREEN_REGISTER_HIGH (0x19 | 0x80)
#define BLUE_REGISTER_LOW (0x1A | 0x80)
#define BLUE_REGISTER_HIGH (0x1B | 0x80)

void color_sensor_init();
status color_sensor_POST_Test();
uint8_t getColorSensorRegisterValue(status* deviceStatus, uint8_t reg);

#endif

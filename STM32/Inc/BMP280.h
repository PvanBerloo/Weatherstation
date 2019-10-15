/*
 * BMP280.h
 *
 *  Created on: 14 okt. 2019
 *      Author: Justin Maas
 */

#ifndef BMP280_H_
#define BMP280_H_

#include "stm32f0xx_hal.h"

/* Reads temperature data from the BMP280.
 * I2C_HandleTypeDef* i2c	- The handle to the i2c interface that the BMP280 is connected to.
 * float* temperature		- Variable to write the temperature data to.
 * uint32_t timeout			- Timeout for the i2c interface in milliseconds.
 *
 * returns the status of the i2c operations, HAL_OK if successfull.
 */
HAL_StatusTypeDef BMP280_readTemperature(I2C_HandleTypeDef* i2c, float* temperature, uint32_t timeout);

/* Reads humidity data from the BMP280.
 * I2C_HandleTypeDef* i2c	- The handle to the i2c interface that the BMP280 is connected to.
 * float* pressure			- Variable to write the pressure data to.
 * uint32_t timeout			- Timeout for the i2c interface in milliseconds.
 *
 * returns the status of the i2c operations, HAL_OK if successfull.
 */
HAL_StatusTypeDef BMP280_readPressure(I2C_HandleTypeDef* i2c, float* pressure, uint32_t timeout);

#endif /* BMP280_H_ */

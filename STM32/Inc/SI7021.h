/*
 * SI7021.h
 *
 *  Created on: 20 sep. 2019
 *      Author: paulu
 */

#ifndef SI7021_H_
#define SI7021_H_

#include "stm32f0xx_hal.h"

/* Reads temperature data from the SI7021.
 * I2C_HandleTypeDef* i2c	- The handle to the i2c interface that the SI7021 is connected to.
 * float* temperature		- Variable to write the temperature data to.
 * uint32_t timeout			- Timeout for the i2c interface in milliseconds.
 *
 * returns the status of the i2c operations, HAL_OK if successfull.
 */
HAL_StatusTypeDef SI7021_readTemperature(I2C_HandleTypeDef* i2c, float* temperature, uint32_t timeout);

/* Reads humidity data from the SI7021.
 * I2C_HandleTypeDef* i2c	- The handle to the i2c interface that the SI7021 is connected to.
 * float* humidity			- Variable to write the humidity data to.
 * uint32_t timeout			- Timeout for the i2c interface in milliseconds.
 *
 * returns the status of the i2c operations, HAL_OK if successfull.
 */
HAL_StatusTypeDef SI7021_readHumidity(I2C_HandleTypeDef* i2c, float* humidity, uint32_t timeout);

#endif /* SI7021_H_ */

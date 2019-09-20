/*
 * SI7021.h
 *
 *  Created on: 20 sep. 2019
 *      Author: paulu
 */

#ifndef SI7021_H_
#define SI7021_H_

#include "stm32f0xx_hal.h"

HAL_StatusTypeDef SI7021_readTemperature(I2C_HandleTypeDef* i2c, float* temperature, uint32_t timeout);
HAL_StatusTypeDef SI7021_readHumidity(I2C_HandleTypeDef* i2c, float* humidity, uint32_t timeout);

#endif /* SI7021_H_ */

/*
 * BMP280.h
 *
 *  Created on: 14 okt. 2019
 *      Author: Justin Maas
 */

#ifndef BMP280_H_
#define BMP280_H_

#include "stm32f0xx_hal.h"

typedef enum BMP280_OVERSAMPLING {
	BMP280_OVERSAMPLING_SKIP = 0,
	BMP280_OVERSAMPLING_1 = 1,
	BMP280_OVERSAMPLING_2 = 2,
	BMP280_OVERSAMPLING_4 = 3,
	BMP280_OVERSAMPLING_16 = 5
} BMP280_OVERSAMPLING;

typedef enum BMP280_POWERMODE {
	BMP280_POWERMODE_SLEEP = 0,
	BMP280_POWERMODE_FORCED = 1,
	BMP280_POWERMODE_NORMAL = 3
} BMP280_POWERMODE;

/* Reads the values that will be used for the temperature and pressure calculations.
 * I2C_HandleTypeDef* i2c			- The handle to the i2c interface that the BMP280 is connected to.
 */
void BMP280_readCompensationRegisters(I2C_HandleTypeDef* i2c);

/* Sets the config register of the BMP280.
 * I2C_HandleTypeDef* i2c			- The handle to the i2c interface that the BMP280 is connected to.
 * uint8_t temperatureOversampling.	- Temperature oversampling, 1x, 2x, 4x, 8x, 16x, or none.
 * uint8_t pressureOversampling		- Pressure oversampling, 1x, 2x, 4x, 8x, 16x, or none.
 * uint8_t powerMode				- Powermode, sleep, forced or none.
 */
void BMP280_setConfigRegister(I2C_HandleTypeDef* i2c, BMP280_OVERSAMPLING temperatureOversampling, BMP280_OVERSAMPLING pressureOversampling, BMP280_POWERMODE powerMode);

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

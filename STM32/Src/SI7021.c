/*
 * SI7021.c
 *
 *  Created on: 20 sep. 2019
 *      Author: paulu
 */

#include "SI7021.h"

#define SI7021_ADDRESS 	(0x40<<1)
#define CMD_TEMP 0xE3
#define CMD_HUMIDITY 0xE5

// Sends a command to the SI7021 over I2C and reads the result.
// uint8_t command is CMD_TEMP to read temperature and CMD_HUMIDITY to read humidity.
HAL_StatusTypeDef SI7021_readValue(I2C_HandleTypeDef* i2c, uint8_t command, uint16_t* result, uint32_t timeout)
{
	uint8_t buffer[2] = {0, 0};

	HAL_StatusTypeDef status;

	status = HAL_I2C_Master_Transmit(i2c, SI7021_ADDRESS, &command, 1, timeout);

	if (status != HAL_OK)
		return status;

	status = HAL_I2C_Master_Receive(i2c, SI7021_ADDRESS, buffer, 2, timeout);

	if (status != HAL_OK)
		return status;

	*result = buffer[0] << 8 | buffer[1];

	return HAL_OK;
}

// Converts the value retrieved from the SI7021 to Celcius. See the SI7021 datasheet.
float SI7021_convertTemperature(uint16_t temperature_value)
{
	return (175.72f  * temperature_value)/(65536.0f) - 46.85f;
}

// Converts the value retrieved from the SI7021 to a humidity percentage. See the SI7021 datasheet.
float SI7021_convertHumidity(uint16_t humidity_value)
{
	return (125  * humidity_value)/(65536.0) - 6.0;
}

HAL_StatusTypeDef SI7021_readTemperature(I2C_HandleTypeDef* i2c, float* temperature, uint32_t timeout)
{
	uint16_t result = 0;

	HAL_StatusTypeDef status = SI7021_readValue(i2c, CMD_TEMP, &result, timeout);

	if (status != HAL_OK)
		return status;

	*temperature = SI7021_convertTemperature(result);

	return HAL_OK;
}

HAL_StatusTypeDef SI7021_readHumidity(I2C_HandleTypeDef* i2c, float* humidity, uint32_t timeout)
{
	uint16_t result = 0;

	HAL_StatusTypeDef status = SI7021_readValue(i2c, CMD_HUMIDITY, &result, timeout);

	if (status != HAL_OK)
		return status;

	*humidity = SI7021_convertHumidity(result);

	return HAL_OK;
}

/*
 * BMP280.c
 *
 *  Created on: 14 okt. 2019
 *      Author: Justin Maas
 */

#include "BMP280.h"

#define BMP280_ADDRESS 	(0x77 << 1)
#define CMD_TEMP 		0xFA
#define CMD_PRESSURE 	0xF7

// t_fine carries fine temperature as global value
// will be used in pressure computation
int32_t 	t_fine;

uint16_t	dig_T1;
int16_t 	dig_T2;
int16_t 	dig_T3;

uint16_t 	dig_P1;
int16_t 	dig_P2;
int16_t 	dig_P3;
int16_t 	dig_P4;
int16_t 	dig_P5;
int16_t 	dig_P6;
int16_t 	dig_P7;
int16_t 	dig_P8;
int16_t 	dig_P9;

uint16_t I2C_read_uint16(I2C_HandleTypeDef* i2c, uint8_t address, uint8_t reg)
{
    uint16_t result = 0;

    HAL_I2C_Master_Transmit(i2c, address, &reg, sizeof(uint8_t), 1000);
    HAL_I2C_Master_Receive(i2c, address, (uint8_t*)&result, sizeof(uint16_t), 1000);

    return result;
}

//Trimming parameter readout, used for compensation in BMP280_convertTemperature and BMP280_convertPressure
void BMP280_readCompensationRegisters(I2C_HandleTypeDef* i2c){
	dig_T1 = I2C_read_uint16(i2c, BMP280_ADDRESS, 0x88);
	dig_T2 = I2C_read_uint16(i2c, BMP280_ADDRESS, 0x8A);
	dig_T3 = I2C_read_uint16(i2c, BMP280_ADDRESS, 0x8C);

	dig_P1 = I2C_read_uint16(i2c, BMP280_ADDRESS, 0x8E);
	dig_P2 = I2C_read_uint16(i2c, BMP280_ADDRESS, 0x90);
	dig_P3 = I2C_read_uint16(i2c, BMP280_ADDRESS, 0x92);
	dig_P4 = I2C_read_uint16(i2c, BMP280_ADDRESS, 0x94);
	dig_P5 = I2C_read_uint16(i2c, BMP280_ADDRESS, 0x96);
	dig_P6 = I2C_read_uint16(i2c, BMP280_ADDRESS, 0x98);
	dig_P7 = I2C_read_uint16(i2c, BMP280_ADDRESS, 0x9A);
	dig_P8 = I2C_read_uint16(i2c, BMP280_ADDRESS, 0x9C);
	dig_P9 = I2C_read_uint16(i2c, BMP280_ADDRESS, 0x9E);
}

//  sets the data acquisition options of the device.
// 	uint8_t temperatureOversampling:	Each oversampling step reduces noise and increases the output resolution by one bit
//	uint8_t pressureOversampling:		Each oversampling step reduces noise and increases the output resolution by one bit.
// 	uint8_t powerMode: 					Controls the power mode of the device.
void BMP280_setConfigRegister(I2C_HandleTypeDef* i2c, BMP280_OVERSAMPLING temperatureOversampling, BMP280_OVERSAMPLING pressureOversampling, BMP280_POWERMODE powerMode)
{
    uint8_t data[2] = { 0xF4, (((uint8_t)temperatureOversampling << 5) | ((uint8_t)pressureOversampling << 2)) | (uint8_t)powerMode };

    HAL_I2C_Master_Transmit(i2c, BMP280_ADDRESS, data, sizeof(data), 1000);
}

// Sends a command to the BMP280 over I2C and reads the result.
// uint8_t command is CMD_TEMP to read temperature and CMD_PRESSURE to read pressure.
HAL_StatusTypeDef BMP280_readValue(I2C_HandleTypeDef* i2c, uint8_t command, uint32_t* result, uint32_t timeout)
{
	uint8_t buffer[3] = {0, 0, 0};

	HAL_StatusTypeDef status;

	status = HAL_I2C_Master_Transmit(i2c, BMP280_ADDRESS, &command, sizeof(uint8_t), timeout);

	if (status != HAL_OK)
		return status;

	status = HAL_I2C_Master_Receive(i2c, BMP280_ADDRESS, buffer, sizeof(buffer), timeout);

	if (status != HAL_OK)
		return status;

	*result = buffer[0] << 12 | buffer[1] << 4 | buffer[2];;

	return HAL_OK;
}

// Converts the value retrieved from the BMP280 to Celcius. See the BMP280 datasheet.
int32_t BMP280_convertTemperature(int32_t adc_T)
{
    int32_t var1, var2, T;

    var1 = ((((adc_T>>3) - ((int32_t)dig_T1<<1))) * ((int32_t)dig_T2)) >> 11;
    var2 = (((((adc_T>>4) - ((int32_t)dig_T1)) * ((adc_T>>4) - ((int32_t)dig_T1))) >> 12) *
        ((int32_t)dig_T3)) >> 14;
    t_fine = var1 + var2;
    T = (t_fine * 5 + 128) >> 8;
    return T;
}

// Converts the value retrieved from the BMP280 to a pressure in Pascal. See the BMP280 datasheet.
uint32_t  BMP280_convertPressure(int32_t adc_P)
{
	int64_t var1, var2, p;
	var1 = ((int64_t)t_fine) - 128000;
	var2 = var1 * var1 * (int64_t)dig_P6;
	var2 = var2 + ((var1*(int64_t)dig_P5)<<17);
	var2 = var2 + (((int64_t)dig_P4)<<35);
	var1 = ((var1 * var1 * (int64_t)dig_P3)>>8) + ((var1 * (int64_t)dig_P2)<<12);
	var1 = (((((int64_t)1)<<47)+var1))*((int64_t)dig_P1)>>33;
	if (var1 == 0)
	{
		return 0; // avoid exception caused by division by zero
	}
	p = 1048576-adc_P;
	p = (((p<<31)-var2)*3125)/var1;
	var1 = (((int64_t)dig_P9) * (p>>13) * (p>>13)) >> 25;
	var2 = (((int64_t)dig_P8) * p) >> 19;
	p = ((p + var1 + var2) >> 8) + (((int64_t)dig_P7)<<4);
	return (uint32_t)p;
}

HAL_StatusTypeDef BMP280_readTemperature(I2C_HandleTypeDef* i2c, float* temperature, uint32_t timeout)
{
	uint32_t result = 0;

	HAL_StatusTypeDef status = BMP280_readValue(i2c, CMD_TEMP, &result, timeout);

	if (status != HAL_OK)
		return status;

	*temperature = BMP280_convertTemperature(*(int32_t*)&result)/100.0f;

	return HAL_OK;
}

HAL_StatusTypeDef BMP280_readPressure(I2C_HandleTypeDef* i2c, float* pressure, uint32_t timeout)
{
	uint32_t result = 0;

	HAL_StatusTypeDef status = BMP280_readValue(i2c, CMD_PRESSURE, &result, timeout);

	if (status != HAL_OK)
		return status;

	*pressure = BMP280_convertPressure(*(int32_t*)&result)/25600.0f;

	return HAL_OK;
}

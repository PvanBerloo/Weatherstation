/*
 * ESP8266.h
 *
 *  Created on: 26 okt. 2019
 *      Author: Paul
 */

#ifndef ESP8266_H_
#define ESP8266_H_

#include "stm32f0xx_hal.h"

typedef enum ESP8266_MODE {
	ESP8266_MODE_STATION = 1,
	ESP8266_MODE_SOFTAP = 2,
	ESP8266_MODE_BOTH = 3
} ESP8266_MODE;

/* Reads the values that will be used for the temperature and pressure calculations.
 * UART_HandleTypeDef* uart			- The handle to the uart interface that the ESP8266 is connected to.
 * ESP8266_MODE mode				- The mode that the ESP8266 should be configured to.
 * int flash						- 1 when the mode should be stored in flash memory, 0 when not.
 * uint32_t timeout					- The timeout for each uart operation.
 */
void ESP8266_setMode(UART_HandleTypeDef* uart, ESP8266_MODE mode, int flash, uint32_t timeout);

/* Reads the values that will be used for the temperature and pressure calculations.
 * UART_HandleTypeDef* uart			- The handle to the uart interface that the ESP8266 is connected to.
 * const char* ssid					- The SSID of the network to connect to.
 * const char* password				- The password of the network to connect to.
 * int flash						- 1 when the mode should be stored in flash memory, 0 when not.
 * uint32_t timeout					- The timeout for each uart operation.
 */
void ESP8266_connectToAP(UART_HandleTypeDef* uart, const char* ssid, const char* password, int flash, uint32_t timeout);

/* Enables the deep-sleep mode of the ESP8266.
 * UART_HandleTypeDef* uart			- The handle to the uart interface that the ESP8266 is connected to.
 */
void ESP8266_deepSleep(UART_HandleTypeDef* uart);

void ESP8266_createTCPConnection(UART_HandleTypeDef* uart, const char* address, int port, uint32_t timeout);

void ESP8266_sendData(UART_HandleTypeDef* uart, const uint8_t* data, int length, uint32_t timeout);


#endif /* ESP8266_H_ */

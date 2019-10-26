/*
 * ESP8266.c
 *
 *  Created on: 26 okt. 2019
 *      Author: Paul
 */

#include "ESP8266.h"

#include <string.h>

const char str_cur[] = "CUR";
const char str_def[] = "DEF";

void ESP8266_setMode(UART_HandleTypeDef* uart, ESP8266_MODE mode, int flash, uint32_t timeout)
{
	char str_cwmode[] = "AT+CWMODE_";

	char str_end[] = {'=', mode + '0', '\r', '\n'};

	HAL_UART_Transmit(uart, str_cwmode, strlen(str_cwmode), timeout);

	if (flash)
	{
		HAL_UART_Transmit(uart, str_def, strlen(str_def), timeout);
	}
	else
	{
		HAL_UART_Transmit(uart, str_cur, strlen(str_cur), timeout);
	}

	HAL_UART_Transmit(uart, str_end, strlen(str_end), timeout);
}

void ESP8266_connectToAP(UART_HandleTypeDef* uart, const char* ssid, const char* password, int flash, uint32_t timeout)
{
	char str_cwjap[] = "AT+CWJAP_";
	char str_equals[] = "=\"";
	char str_comma[] = "\",\"";
	char str_end[] = "\"\r\n";

	HAL_UART_Transmit(uart, str_cwjap, strlen(str_cwjap), timeout);

	if (flash)
	{
		HAL_UART_Transmit(uart, str_def, strlen(str_def), timeout);
	}
	else
	{
		HAL_UART_Transmit(uart, str_cur, strlen(str_cur), timeout);
	}

	HAL_UART_Transmit(uart, str_equals, strlen(str_equals), timeout);
	HAL_UART_Transmit(uart, ssid, strlen(ssid), timeout);
	HAL_UART_Transmit(uart, str_comma, strlen(str_comma), timeout);
	HAL_UART_Transmit(uart, password, strlen(password), timeout);
	HAL_UART_Transmit(uart,str_end, strlen(str_end), timeout);
}

void ESP8266_deepSleep(UART_HandleTypeDef* uart)
{
	// time does not matter because the ESP can't wake itself up when the RTC interrupt is not wired to the reset.
	char buffer[] = "AT+GSLP=1\r\n";
	HAL_UART_Transmit(uart, (uint8_t*)buffer, strlen(buffer), 1000);
}

void ESP8266_createTCPConnection(UART_HandleTypeDef* uart, const char* address, int port, uint32_t timeout)
{
	char str_cipstart[] = "AT+CIPSTART=\"TCP\",\"";
	char str_comma[] = "\",";
	char str_port[6];
	char str_end[] = "\r\n";

	snprintf(str_port, sizeof(str_port), "%i", port);

	HAL_UART_Transmit(uart, str_cipstart, strlen(str_cipstart), timeout);
	HAL_UART_Transmit(uart, address, strlen(address), timeout);
	HAL_UART_Transmit(uart, str_comma, strlen(str_comma), timeout);
	HAL_UART_Transmit(uart, str_port, strlen(str_port), timeout);
	HAL_UART_Transmit(uart, str_end, strlen(str_end), timeout);
}

void ESP8266_sendData(UART_HandleTypeDef* uart, const uint8_t* data, int length, uint32_t timeout)
{
	char str_cipsend[] = "AT+CIPSEND=";
	char str_bytes[5]; // max packet size is 2048 bytes + \0 character
	char str_end[] = "\r\n";

	snprintf(str_bytes, sizeof(str_bytes), "%i", length);

	HAL_UART_Transmit(uart, str_cipsend, strlen(str_cipsend), timeout);
	HAL_UART_Transmit(uart, str_bytes, strlen(str_bytes), timeout);
	HAL_UART_Transmit(uart, str_end, strlen(str_end), timeout);

	// Give some time to let the ESP process
	osDelay(1000);

	HAL_UART_Transmit(uart, data, length, timeout);
}

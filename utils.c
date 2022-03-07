/*
 * utils.c
 *
 *  Created on: Mar 6, 2022
 *      Author: root
 */
#include "main.h"
#include "string.h"
#include "usart.h"

void Uart_Message(char *Message) {
	HAL_UART_Transmit(&huart2, (uint8_t*) Message, strlen(Message), 1000);
}

/*
 * zenith.c
 *
 *  Created on: Jan 28, 2022
 *      Author: leocelente
 */

#include "main.h"

/* Override putchar so printf outputs to UART1 */
extern UART_HandleTypeDef huart1;
int __io_putchar(int ch){
	return !HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1, 10);
}

#ifndef __USER_UART_H
#define __USER_UART_H

#include "stdint.h"
#include "main.h"
#include "stm32f1xx_hal_uart.h"


void MX_USART1_UART_Init(void);
void MX_UART4_Init(void);
int fputc(int ch, FILE *f);
int fgetc(FILE *f);

#endif

#ifndef __USER_RS485_H
#define __USER_RS485_H

#include "stdint.h"
#include "main.h"
#include "stm32f1xx_hal_uart.h"
#include "user_uart.h"
#include "user_app.h"
#include "stm32f1xx_it.h"


extern UART_HandleTypeDef huart4;

void RS485_init(void);
HAL_StatusTypeDef RS485_SendData(uint8_t data);
uint16_t RS485_RecieveData(uint16_t data);
ErrorStatus RS485_RecieveData_IT(void);
void RS485_IRQHandler(void);

void RS485_RX_IRQ_ENABLE(void);

#endif

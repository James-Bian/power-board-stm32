#ifndef __USER_APP_H
#define __USER_APP_H

#include "main.h"
#include "user_uart.h"


/* Private function prototypes -----------------------------------------------*/

#define LOG printf


extern I2C_HandleTypeDef hi2c1;

void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_I2C1_Init(void);


#endif

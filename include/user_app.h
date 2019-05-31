#ifndef __USER_APP_H
#define __USER_APP_H

#include "main.h"
#include "user_uart.h"


/* Private function prototypes -----------------------------------------------*/

#define LOG printf

extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;
extern ADC_HandleTypeDef hadc3;

extern DAC_HandleTypeDef hdac;

extern I2C_HandleTypeDef hi2c1;

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim8;

void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_ADC1_Init(void);
void MX_ADC2_Init(void);
void MX_ADC3_Init(void);
void MX_DAC_Init(void);
void MX_TIM2_Init(void);
void MX_I2C1_Init(void);
void MX_TIM8_Init(void);
void MX_TIM3_Init(void);

#endif

/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/

#include "user_app.h"

I2C_HandleTypeDef hi2c1;

/**
  * @brief  The application entry point.
  * @retval int
  */
extern PowerSettingDef PowerFlashSetting;

int main(void)
{

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_ADC3_Init();
  MX_DAC_Init();
  MX_TIM2_Init();
  MX_I2C1_Init();
  MX_UART4_Init();
  MX_USART1_UART_Init();
  MX_TIM8_Init();
  MX_TIM3_Init();
	
	//HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_3);
	//HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
	
	//HAL_DAC_SetValue(&hdac,DAC_CHANNEL_1,DAC_ALIGN_12B_R,10);
	//HAL_DAC_Start(&hdac,DAC_CHANNEL_1);
	
	//HAL_DAC_SetValue(&hdac,DAC_CHANNEL_2,DAC_ALIGN_12B_R,2300); //2370---0.78V,1300-5V,
	//HAL_DAC_Start(&hdac,DAC_CHANNEL_2);	
	LOG("HAL Version:%08x \r\n", HAL_GetHalVersion()); 
	LOG("REVID:%08x \r\n", HAL_GetREVID());
	LOG("DEVID:%08x \r\n", HAL_GetDEVID());
	LOG("Wellcome using power board!\r\n");
	
	LoadFlashSetting(PowerFlashSetting);
	
  while (1)
  {
    PowerSettingCheck();
		PowerMonitor();
  }

}



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

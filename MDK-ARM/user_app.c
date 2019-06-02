#include "user_app.h"

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}



/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}




/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14|GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC13 PC14 PC15 PC0 
                           PC1 PC2 PC3 PC7 
                           PC9 PC12 */
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_0 
                          |GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_7 
                          |GPIO_PIN_9|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA0 PA6 PA11 PA12 
                           PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_6|GPIO_PIN_11|GPIO_PIN_12 
                          |GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PC4 PC5 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PB0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB1 PB2 PB10 PB12 
                           PB13 PB15 PB3 PB4 
                           PB8 PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10|GPIO_PIN_12 
                          |GPIO_PIN_13|GPIO_PIN_15|GPIO_PIN_3|GPIO_PIN_4 
                          |GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB14 PB5 */
  GPIO_InitStruct.Pin = GPIO_PIN_14|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PA8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PD2 */
  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

uint16_t PowerCmd=0;

PowerSettingDef PowerBasicSetting;
PowerSettingDef PowerFlashSetting;

uint32_t FlashSettingData[30]={0,1,2,3,4};
uint32_t FlashAddress = 0x0803F800;

ErrorStatus VoltageSetting(uint16_t value)
{
	return SUCCESS;
}
ErrorStatus CurrentSetting(uint16_t value)
{
	return SUCCESS;
}

ErrorStatus SetDuty(uint16_t duty)
{
	return SUCCESS;
}
ErrorStatus SetFrequency(uint16_t Freq)
{
	return SUCCESS;
}


ErrorStatus SetDelayTime(uint16_t Delaytime)
{
	return SUCCESS;
}

void PowerSet(PowerSettingDef pra )
{
 	if(pra.Status.CVchage!= 0) 
		{
			LOG("Set voltage\r\n");
			VoltageSetting(pra.voltage);       
			pra.Status.CVchage=0;
		}
	if(pra.Status.CCchage!= 0) 
		{
			LOG("Set current\r\n");
			CurrentSetting(pra.Current);       
			pra.Status.CCchage=0;
		}
	if(pra.Status.DutyChage!= 0) 
		{
		  LOG("Set Duty\r\n");
		  SetDuty(pra.Duty);
  		pra.Status.DutyChage=0;
		}
	if(pra.Status.FreqencyChange  != 0)
		{
		  LOG("Set Frequency\r\n");
			SetFrequency(pra.Frequency); 
		  pra.Status.FreqencyChange=0;
		}
	if(pra.Status.DelayTimeChange != 0) 
		{
		 LOG("Set Delay time\r\n");
		 SetDelayTime(pra.DelayTime); 
		 pra.Status.DelayTimeChange=0;
		}
}

ErrorStatus ReadSettingFromFlash(void)
{
	
	LOG("Reading Setting From FLASH\r\n");
	for(uint16_t i=0;i<30;i++)
		{
			FlashSettingData[i]=*(__IO uint32_t*)(FlashAddress+8*i);
			LOG("ReadFlashAddress %08x, %08x\r\n",FlashAddress+8*i,FlashSettingData[i]);
    }	
	return SUCCESS;
}

/*Set setting to Flash*/
uint8_t SaveSettingToFlash(PowerSettingDef pra)
{
	HAL_FLASH_Unlock();  //Unlock Flash;
	
	FLASH_EraseInitTypeDef flashdata;  //init Erease data;
	
	flashdata.TypeErase = FLASH_TYPEERASE_PAGES;
	flashdata.PageAddress = FlashAddress;
	flashdata.NbPages = 1;
	uint32_t PageError = 0;
	
	//Erease Flash
  HAL_FLASHEx_Erase(&flashdata, &PageError);
	
	if(pra.OutputChannel==OutputCh1){
   for(uint16_t i=0;i<10;i++){
			HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, FlashAddress+i*8,  (uint64_t)FlashSettingData[i]);
			LOG("WriteAddress%08x:%08x\r\n",FlashAddress+i*8, *(__IO uint32_t*)(FlashAddress+i*8));
		}
	}
	if(pra.OutputChannel==TriggerOUT1){
	 for(uint16_t i=10;i<20;i++){
			HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, FlashAddress+i*8,  (uint64_t)FlashSettingData[i]);
			LOG("WriteAddress%08x:%08x\r\n",FlashAddress+i*8, *(__IO uint32_t*)(FlashAddress+i*8));
		}
	}
	if(pra.OutputChannel==TriggerOUT2){
	for(uint16_t i=20;i<30;i++){
			HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, FlashAddress+i*8,  (uint64_t)FlashSettingData[i]);
			LOG("WriteAddress%08x:%08x\r\n",FlashAddress+i*8, *(__IO uint32_t*)(FlashAddress+i*8));
		}
	}

		
	HAL_FLASH_Lock();  //lock flash;
	
	return 0;	
}

//Check the settings,compare with the Flash setting;
void PowerSettingCheck(void)
{
	if(PowerFlashSetting.Status.CVchage         == 0 ||
		 PowerFlashSetting.Status.CCchage         == 0 ||
     PowerFlashSetting.Status.DutyChage       == 0 ||
		 PowerFlashSetting.Status.FreqencyChange  == 0 ||
	   PowerFlashSetting.Status.DelayTimeChange == 0    ){
		 LOG("Setting no change\r\n");
		 return;
		}
	else{			
			LOG("Start to save new setting\r\n");
			SaveSettingToFlash(PowerBasicSetting);
			ReadSettingFromFlash();
			return;
		}
}

/*Set the power board with Flash settings*/
ErrorStatus LoadFlashSetting(PowerSettingDef pra)
{ 
	ReadSettingFromFlash();	
	PowerSet(pra);
	return SUCCESS;
}

void PowerMonitor(void)
{
	if(PowerFlashSetting.mode==CV)
	{
	  
	}
	else if(PowerFlashSetting.mode==CC)
	{
	  
	}
	else return;  
}


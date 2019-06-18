#include "user_app.h"

uint16_t PowerCmd=0;

PowerSettingDef PowerBasicSetting;
PowerSettingDef PowerFlashSetting;

PowerSettingDef TriggerOUT1Setting;
PowerSettingDef TriggerOUT2Setting;

uint32_t FlashSettingData[30]={0,1,2,3,4};
uint32_t FlashAddress = 0x0803F800;


extern DAC_HandleTypeDef hdac;
#define ADC_FOR_POWER DAC_CHANNEL_2
#define DAC_FOR_CC DAC_CHANNEL_1

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



ErrorStatus VoltageSetting(uint32_t Data)
{
	uint32_t value;
	value=Data;
/*	
	if(Data<1300){
		LOG("Unsupport value,to set min value 1300!output is around 5V\r\n");
		value=1300;	
	}
	else if(Data>2370&&Data<2500){
		LOG("Unsupport value,to set max vlaue 2370,output is around 0.8V\r\n");
		value=2370;
	}
	else if(Data>2500){
		LOG("Set power off\r\n");// set power off
	}
	else {
		value=Data;
	}
*/
	//LOG("Set ADC value for power:%d\r\n",value);
	HAL_DAC_SetValue(&hdac,ADC_FOR_POWER,DAC_ALIGN_12B_R,value); //2370---0.78V,1300-5V,
	HAL_DAC_Start(&hdac,ADC_FOR_POWER);	
	return SUCCESS;
}


ErrorStatus CC_VoltageSetting(uint32_t Data)
{
	uint32_t value;
	value=Data;
	//LOG("Set DAC value for CC mode:%d\r\n",value);
	HAL_DAC_SetValue(&hdac,DAC_FOR_CC,DAC_ALIGN_12B_R,value); 
	HAL_DAC_Start(&hdac,DAC_FOR_CC);	
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
	VoltageSetting(1800); //for test; 
 	if(pra.Status.CVchangeFlag!= 0) 
		{
			LOG("Set voltage\r\n");
			VoltageSetting(pra.voltage);       
			pra.Status.CVchangeFlag=0;
		}
	if(pra.Status.CCchangeFLag!= 0) 
		{
			LOG("Set current\r\n");
			CurrentSetting(pra.Current);       
			pra.Status.CCchangeFLag=0;
		}
	if(pra.Status.DutyChangeFLag!= 0) 
		{
		  LOG("Set Duty\r\n");
		  SetDuty(pra.Duty);
  		pra.Status.DutyChangeFLag=0;
		}
	if(pra.Status.FreqencyChangeFLag  != 0)
		{
		  LOG("Set Frequency\r\n");
			SetFrequency(pra.Frequency); 
		  pra.Status.FreqencyChangeFLag=0;
		}
	if(pra.Status.DelayTimeChangeFLag != 0) 
		{
		 LOG("Set Delay time\r\n");
		 SetDelayTime(pra.DelayTime); 
		 pra.Status.DelayTimeChangeFLag=0;
		}
}

ErrorStatus ReadSettingFromFlash(void)
{	
	LOG("Reading Setting From FLASH\r\n");
	for(uint16_t i=0;i<30;i++)
		{
			FlashSettingData[i]=*(__IO uint32_t*)(FlashAddress+8*i);
			LOG("FlashData %08x\r\n",FlashSettingData[i]);
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
	if(PowerFlashSetting.Status.CVchangeFlag         == 0 ||
		 PowerFlashSetting.Status.CCchangeFLag         == 0 ||
     PowerFlashSetting.Status.DutyChangeFLag       == 0 ||
		 PowerFlashSetting.Status.FreqencyChangeFLag   == 0 ||
	   PowerFlashSetting.Status.DelayTimeChangeFLag  == 0    ){
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



extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;
extern ADC_HandleTypeDef hadc3;

uint32_t MeasureVoltage(ADC_HandleTypeDef * ADCname)
{
	uint32_t temp;	
	HAL_ADC_Start(ADCname);
	temp=HAL_ADC_GetValue(ADCname);
	//HAL_ADC_Stop(ADCname);
	//LOG("ADC2_IN2,POWER_OUT:%f\r\n",(double)temp*66/40950);     //4095*33/10);
	return temp;
}

uint32_t MeasureCurrent(ADC_HandleTypeDef *ADCname)
{
	uint32_t temp;	
	HAL_ADC_Start(ADCname);
	temp=HAL_ADC_GetValue(ADCname);
	////HAL_ADC_Stop(ADCname);
	//LOG("ADC1_IN1,POWER_OUT_CURRENT:%f\r\n",(double)temp*33/12370);
	return temp;
}

void SetVotageDac(uint16_t reg)
{
 
}

uint32_t DacVaule;

/*void PowerMonitor(void)
{
	uint32_t voltage,tmp;
	uint32_t current;
	if(PowerFlashSetting.mode==CV)
	{	  
		voltage=(double)MeasureVoltage(&hadc2)*6600/4095;                             //DAC:2370--0.7V ,1300=5V;
		tmp=((voltage/1000)<<12)+(((voltage%1000)/100)<<8)+((voltage%100)/10<<4)+(voltage%10);
		LOG("CV mode Voltage:%x\r\n",tmp);
		if(tmp<PowerFlashSetting.voltage){
			VoltageSetting(DacVaule--);
			HAL_Delay(10);
			}
		else{
			VoltageSetting(DacVaule++);
HAL_Delay(10);			
			} 			
	}
	else if(PowerFlashSetting.mode==CC)
	{
				
	  current=(double)MeasureCurrent(&hadc1)*3300/1237; 
		tmp=((current/1000)<<12)+(((current%1000)/100)<<8)+((current%100)/10<<4)+(current%10);
    LOG("CC mode current:%x\r\n",tmp);
		if(tmp<PowerFlashSetting.Current){
			if(DacVaule<=2370){
		  VoltageSetting(DacVaule--);
			}	
		}
		else{
			VoltageSetting(DacVaule++);
		}
		if(DacVaule>2370){
		DacVaule=2370;
		}
				if(DacVaule<1300){
		DacVaule=1300;
		}		
	}
	else return;  
}
*/

void PowerMonitor(void)
{
	uint64_t voltage,tmp;
	uint32_t current;
	if(PowerFlashSetting.mode==CV)
	{	  
		voltage=(double)MeasureVoltage(&hadc2)*6600/4095;                             //DAC:2370--0.7V ,1300=5V;
		tmp=((voltage/1000)<<12)+(((voltage%1000)/100)<<8)+((voltage%100)/10<<4)+(voltage%10);
		LOG("CV mode Voltage:%x\r\n",(unsigned int)tmp);
		tmp=PowerFlashSetting.voltage*3300/4095;
		LOG("CV DAC:%d\r\n",(unsigned int)PowerFlashSetting.voltage);
    VoltageSetting(tmp);			
	}
	else if(PowerFlashSetting.mode==CC)
	{				
	  current=(double)MeasureCurrent(&hadc1)*330000/123669; 
		tmp=((current/1000)<<12)+(((current%1000)/100)<<8)+((current%100)/10<<4)+(current%10);
    LOG("CC mode current measure:%x\r\n",(unsigned int)tmp);
		tmp=PowerFlashSetting.Current*123669/330000;
		LOG("set current:%d\r\n",PowerFlashSetting.Current);
		LOG("set CC DAC:%d\r\n",(unsigned int)tmp);
    CC_VoltageSetting(tmp);	
	}
	else return;  
}

void TriggerSettingCheck(void)
{
	if(TriggerOUT1Setting.Status.DutyChangeFLag!=0     ||
		 TriggerOUT1Setting.Status.FreqencyChangeFLag!=0 ||
		 TriggerOUT1Setting.Status.DelayTimeChangeFLag!=0  ){
		 TriggerSetting(TriggerOUT1Setting.Duty,TriggerOUT1Setting.Frequency,TriggerOUT1Setting.DelayTime);	
		 SaveSettingToFlash(TriggerOUT1Setting);		 
		 }
	if(TriggerOUT2Setting.Status.DutyChangeFLag!=0     ||
		 TriggerOUT2Setting.Status.FreqencyChangeFLag!=0 ||
		 TriggerOUT2Setting.Status.DelayTimeChangeFLag!=0  ){
		 TriggerSetting(TriggerOUT2Setting.Duty,TriggerOUT2Setting.Frequency,TriggerOUT2Setting.DelayTime);
		 SaveSettingToFlash(TriggerOUT2Setting);
		 }
	return;
}

void TriggerSetting(uint32_t Duty,uint32_t Frequency,uint32_t Delaytime)
{
      
}

void KeyProcess(void)
{
  if(CV_KEY_LEVEL==0)		
	{
		PowerFlashSetting.mode=CV;
		CC_VoltageSetting(0xFFFF);
	}
	  if(CC_KEY_LEVEL==0)		
	{
		PowerFlashSetting.mode=CC;
		VoltageSetting(0xFFFF);
	}
	if(PowerFlashSetting.mode==CV&&KEY_N_LEVEL==0&&PowerFlashSetting.voltage>0x0000)
	{
		while(!KEY_N_LEVEL);
		PowerFlashSetting.voltage--;
		//if(PowerFlashSetting.voltage==0x0800)
	  //PowerFlashSetting.voltage=0x0800;	
	}
	if(PowerFlashSetting.mode==CV&&KEY_P_LEVEL==0&&PowerFlashSetting.voltage<0x5100)
	{
		HAL_Delay(1);
		while(!KEY_P_LEVEL);
		PowerFlashSetting.voltage++;	
		//if(PowerFlashSetting.voltage==5000)
	  //PowerFlashSetting.voltage=0x4FFF;	
	}
		if(PowerFlashSetting.mode==CC&&KEY_N_LEVEL==0)
	{
		HAL_Delay(1);
		while(!KEY_N_LEVEL);
		PowerFlashSetting.Current--;
		//if(PowerFlashSetting.Current==0x0080)
		//PowerFlashSetting.Current=0x0081;
	}
	if(PowerFlashSetting.mode==CC&&KEY_P_LEVEL==0)
	{
		HAL_Delay(1);
		while(!KEY_P_LEVEL);
		PowerFlashSetting.Current++;	
		//if(PowerFlashSetting.Current==0xA100)
		//PowerFlashSetting.Current=0xA0FF;
	}
}


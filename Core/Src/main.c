#include "user_app.h"

I2C_HandleTypeDef hi2c1;

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

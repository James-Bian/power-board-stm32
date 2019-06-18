#include "user_app.h"

I2C_HandleTypeDef hi2c1;

extern PowerSettingDef PowerFlashSetting;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim8;
uint8_t ChangeFlag=0;

extern uint32_t DacVaule;


uint8_t aTxBuffer[20];
uint8_t aRxBuffer1[20]; 

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
  //MX_I2C1_Init();
  RS485_init();
  RS485_RX_IRQ_ENABLE();
	
  MX_USART1_UART_Init();
  MX_TIM8_Init();
  MX_TIM3_Init();
	
	LOG("HAL Version:%08x \r\n", HAL_GetHalVersion()); 
	LOG("REVID:%08x \r\n", HAL_GetREVID());
	LOG("DEVID:%08x \r\n", HAL_GetDEVID());
	LOG("Wellcome using power board!\r\n");
	
	LoadFlashSetting(PowerFlashSetting);
	//HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	//HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
	//HAL_Delay(1);
	//HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
	
	PowerFlashSetting.voltage=500;  //
	//PowerFlashSetting.Status.CVchangeFlag=0;
	LOG("PowerFlashSetting.voltage%d\r\n",PowerFlashSetting.voltage);
	
	//PowerFlashSetting.Current=100;
  //DacVaule=3300;
	PowerFlashSetting.Status.CVchangeFlag=1;
	PowerFlashSetting.mode=CV;
	
	//VoltageSetting(800);
	//while(1);
	
  while (1)
	{
		if(ChangeFlag!=0){
    PowerSettingCheck();     //Checking the PowerOUT parameters;
		TriggerSettingCheck();   //Checking the PWM setting ,include the POWER and trigger setting;
		}
		KeyProcess();
		PowerMonitor();          //Monitor the CV or CC mode , modify the parameters if the offseting occures;
		//RS485_SendData(0x11);
		//LOG("PowerFlashSetting.voltage%0x\r\n",PowerFlashSetting.voltage);
		//LOG("PowerFlashSetting.Current%0x\r\n",PowerFlashSetting.Current);
  }

}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

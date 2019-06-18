#include "user_RS485.h"


void RS485_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  //__HAL_RCC_GPIOB_CLK_ENABLE();
		
	MX_UART4_Init();
	
	//set GPIO level;
	
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);  //make receive data default;
		
	/*Configure GPIO pins : PB14 PB5 */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

HAL_StatusTypeDef RS485_SendData(uint8_t data)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);  //enable TX;
	
  HAL_UART_Transmit(&huart4,(uint8_t *)&data,1,0xFFFF);
	
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);  //enable RX;
	
	return HAL_OK;
}

uint16_t RS485_RecieveData(uint16_t data)
{
	
 return 0; 

}
ErrorStatus RS485_RecieveData_IT(void);

void RS485_RX_IRQ_ENABLE(void)

{
	  __HAL_UART_ENABLE_IT(&huart4,UART_IT_RXNE);  //enable RS485 IT

}


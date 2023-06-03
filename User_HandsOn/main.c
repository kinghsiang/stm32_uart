// ref: https://microcontrollerslab.com/uart-usart-communication-stm32f4-discovery-board-hal-uart-driver/
#include "main.h"
#include "uart.h"
#include <string.h>
uint8_t start[7] = "start\r\n";
uint8_t rxData;

#define RXBUFFERSIZE  256
char RxBuffer[RXBUFFERSIZE];
uint8_t aRxBuffer;
uint8_t Uart2_Rx_Cnt = 0;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(huart);
  /* NOTE: This function Should not be modified, when the callback is needed,
           the HAL_UART_TxCpltCallback could be implemented in the user file
   */
  	  //HAL_UART_Transmit(&huart2, (uint8_t *)"in to RXC", 10,0xFFFF);
	if(Uart2_Rx_Cnt >= 255)  //
	{
		Uart2_Rx_Cnt = 0;
		memset(RxBuffer,0x00,sizeof(RxBuffer));
		HAL_UART_Transmit(&huart2, (uint8_t *)"overflow", 10,0xFFFF);

	}
	else
	{	//HAL_UART_Transmit(&huart2, (uint8_t *)"1", 10,0xFFFF);
		RxBuffer[Uart2_Rx_Cnt++] = aRxBuffer;   //
		//HAL_UART_Transmit(&huart2, (uint8_t *)"2", 10,0xFFFF);
		if((RxBuffer[Uart2_Rx_Cnt-1] == 0x0D)||(RxBuffer[Uart2_Rx_Cnt-2] == 0x0D)) //
		{
			HAL_UART_Transmit(&huart2, (uint8_t *)&RxBuffer, Uart2_Rx_Cnt,0xFFFF); //
			HAL_UART_Transmit(&huart2, (uint8_t *)"\r\n", 10,0xFFFF);
            while(HAL_UART_GetState(&huart2) == HAL_UART_STATE_BUSY_TX);//
			Uart2_Rx_Cnt = 0;
			memset(RxBuffer,0x00,sizeof(RxBuffer)); //清空数组
		}
	}

	HAL_UART_Receive_IT(&huart2, (uint8_t *)&aRxBuffer, 1);   //
}

int main(void)
{
	HAL_Init(); /* HAL library initialization */
	GPIO_D_Configuration(); /* Call UART2 initialization define below */
	UART_Configuration();
	while(1)
	{
		HAL_USART_Transmit(&huart2, (uint8_t *)start, sizeof(start), 10);
		Delay_ms(100);
	}
}


/*Generate ms */
void Delay_ms(volatile int time_ms)
{
	      int j;
        for(j = 0; j < time_ms*4000; j++)
            {}  /* excute NOP for 1ms */
}

void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {

  }
  /* USER CODE END Error_Handler_Debug */
}
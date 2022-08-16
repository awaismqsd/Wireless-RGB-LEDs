/*
 * uart.c
 *
 *  Created on: Feb 19, 2018
 *      Author: awais.maqsood
 */
#include "main.h"
#include "uart.h"
#include "stm32f4xx.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* UART handler declaration */
extern UART_HandleTypeDef UartHandle;

static void Error_Handler(void)
{
  /* Turn LED2 on */
//  BSP_LED_On(LED2);
  while(1)
  {
  }
}


void MX_USART2_UART_Init(void){
	  /*##-1- Configure the UART peripheral ######################################*/
	  /* Put the USART peripheral in the Asynchronous mode (UART Mode) */
	  /* UART1 configured as follow:
	      - Word Length = 8 Bits
	      - Stop Bit = One Stop bit
	      - Parity = ODD parity
	      - BaudRate = 9600 baud
	      - Hardware flow control disabled (RTS and CTS signals) */
	  UartHandle.Instance          = USARTx;

	  UartHandle.Init.BaudRate     = 9600;
	  UartHandle.Init.WordLength   = UART_WORDLENGTH_8B;
	  UartHandle.Init.StopBits     = UART_STOPBITS_1;
	  UartHandle.Init.Parity       = UART_PARITY_NONE;
	  UartHandle.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
	  UartHandle.Init.Mode         = UART_MODE_TX_RX;
	  UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;

	  if(HAL_UART_Init(&UartHandle) != HAL_OK)
	  {
	    /* Initialization Error */
	    Error_Handler();
	  }

	  /* Output a message on Hyperterminal using printf function */
	  //printf("\n\r Uart2 has been Successfully Configured\n\r");


}
/*
void configureBT(void){

	HAL_UART_Transmit(&UartHandle, (uint8_t*)"$", 1, 10);
	HAL_UART_Transmit(&UartHandle, (uint8_t*)"$", 1, 10);
	HAL_UART_Transmit(&UartHandle, (uint8_t*)"$", 1, 10);

}*/
/*
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *haurt) {
	uart_rx_buf[countRead++] = data;
	if (data == '\n') {
			uart_rx_rdy = 1;
			countRead = 0;
		}
		else{

			HAL_UART_Receive_IT(&UartHandle, (uint8_t *) &data, 1);

		}
}
*/
/*
void uart_readln(void) {
	for (int i = 0; i <= 6; i++) {
		uart_rx_buf[i] = 0;
	}
	uart_rx_rdy = 0;
	//uart_rx_err = 0;
	countRead=0;

	HAL_UART_Receive_IT(&UartHandle, (uint8_t *) &data, 1);

}*/
/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */

  /* Place your implementation of fputc here */
  /* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
 // HAL_UART_Transmit(&UartHandle, (uint8_t *)&ch, 1, 0xFFFF);


/**
  ******************************************************************************
  * @file    TIM/TIM_DMA/Src/main.c
  * @author  MCD Application Team
  * @brief   This sample code shows how to use DMA with TIM3 Update request to
  *          transfer Data from memory to TIM3 Capture Compare Register 3 (CCR3).
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "ledDriver.h"
#include "uart.h"
#include "stm32f4xx_hal_uart.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Timer handler declaration */
TIM_HandleTypeDef    TimHandle;
/* Timer Output Compare Configuration Structure declaration */
TIM_OC_InitTypeDef sConfig;
/* Uart handler declaration */
UART_HandleTypeDef UartHandle;

uint8_t data;
uint8_t uart_rx_rdy;
//uint8_t reading=0;



char uart_rx_buf[6];
uint8_t countRead = 0;

char rxArr[6]={"c 000\n"};	//array to receive data from uart in interrupt mode. default is set to c 000\n

int main(void)
{
	MX_USART2_UART_Init();		//Uart initialization
	ws2812Init();				//ws2812 initialization

	static uint8_t red, grn, blu;		//Static variables to store value for colors
	red=0;						//initializing color to 0 as default parameter
	grn=0;
	blu=0;
	//char redCode[4];
	//char grnCode[4];
	//char bluCode[4];
	//char txArr[4];


	char temp[3];	//temp array defined for conversion of ascii to integer
	//const char allCol[11]={"255,255,255"};	//const array to compare and check for All color Command from bluetooth/Serial
	char comp[6];		//Compare array where received data from rxdArr is copied
	//uint16_t ret;		//return parameter from strncmp command that will show us compare result
	uint16_t count=0;	//count for stopping while loop and perform other functions

	while (1)			//Main while loop will not return
	{


		//HAL uart receive function to get data from uart/bluetooth
		//HAL_UART_Receive(&UartHandle, (uint8_t*)&rxArr, 6, 1000);

		//HAL_UART_Receive_IT(&UartHandle, (uint8_t*)&rxArr, 6);
		//if(reading!=1)

		//Receive Commands from Bluetooth/uart using interrupt Mode
		HAL_UART_Receive_IT(&UartHandle, (uint8_t*)&data, 1);


		if (uart_rx_rdy == 1) {				//If Command all 6 characters of command received
			strncpy(rxArr,uart_rx_buf,6);	//Copy uart buffer to rxArr
			uart_rx_rdy=0;					//set the ready flag back to zero
		}
		strncpy(comp,rxArr,6);

		switch(comp[0]){					//switch to case according to value in comp[0]
		case 'r':							//If first byte is r
			strncpy(temp,comp+2,3);			//copy next three bytes to temp
			red= atoi(temp);				//convert temp ascii to int
			setWHOLEcolor(red,grn,blu);		//set the value for all leds
			break;							//Break this case

		case 'g':							//If first byte is g
			strncpy(temp,comp+2,3);			//copy next three bytes to temp
			grn= atoi(temp);				//convert temp ascii to int
			setWHOLEcolor(red,grn,blu);		//set the value for all leds
			break;

		case 'b':							//If first byte is b
			strncpy(temp,comp+2,3);			//copy next three bytes to temp
			blu= atoi(temp);				//convert temp ascii to int
			setWHOLEcolor(red,grn,blu);		//set the value for all leds
			break;


		case 'c':							//If nothing has recieved so far and default value c is there in rxArr
			while(count<=500){				//run the stripEffect for 500 loops
				stripEffect_AllColors(5);	// call the color effect function which will generate colors according to palette
				count++;					//increment count to terminate  while loop
			}
			count=0;						//set the count back to zero in order to execute while loop again
		break;

		}
		//}
		//uart_readln();
		//case 0:
			//while(count<=500){
				//stripEffect_AllColors(5);	// call the color effect function which will generate colors according to palette
				//count++;					//increment count to terminate  while loop
			//}
			//count=0;						//set the count back to zero in order to execute while loop again
			//break;

		//default:							//executed by default when case 1 dont execute
			//copy first three bytes in rxd to temp
			//strncpy(temp,rxd,3);
			//convert ascii to int and assign to red
			//red= atoi(temp);
			//copy next three bytes in rxd to temp
			//strncpy(temp,rxd+4,3);
			//convert ascii to int and assign to grn
			//grn=atoi(temp);
			//copy next three bytes in rxd to temp
			//strncpy(temp,rxd+8,3);
			//convert ascii to int and assign to blu
			//blu=atoi(temp);
			//Hal transmit the red, grn & blu value in hex to uart/bluetooth
			//HAL_UART_Transmit(&UartHandle, (uint8_t*)&red, sizeof(red), 10);
			//HAL_UART_Transmit(&UartHandle, (uint8_t*)&grn, sizeof(grn), 10);
			//HAL_UART_Transmit(&UartHandle, (uint8_t*)&blu, sizeof(blu), 10);
			//sprintf(txArr,"r %d\n",red);
			//HAL_UART_Transmit(&UartHandle, (uint8_t*)&rxArr, 5, 10);
					//set color of all leds according to values of red, grn, blu

			//HAL_Delay(10);					//Hal delay of 10ms

			//HAL_UART_Receive(&UartHandle, (uint8_t*)&rxd,11, 1000);	//Receive data from uart/Bluetooth and update rxd
			//break;


	}

}

//This is the callback function automatically called when something is recieved from uart
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance==USARTx){

		uart_rx_buf[countRead++] = data;
		if (data == '\n') {
				uart_rx_rdy = 1;
				countRead = 0;
				//reading=0;
		}
		else{

			HAL_UART_Receive_IT(&UartHandle, (uint8_t *) &data, 1);
			if(countRead==6)
				countRead=0;
				//reading=1;
		}
	}
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */


//static void SystemClock_Config(void)
//{
//}

//#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
//void assert_failed(uint8_t *file, uint32_t line)
//{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	//trace_printf("Wrong parameters value: file %s on line %d\r\n", file, line);
  /* Infinite loop */
//  while (1)
//  {
//  }
//}

//#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/**
  ******************************************************************************
  * @file    TIM/TIM_DMA/Src/stm32f4xx_hal_msp.c
  * @author  MCD Application Team
  * @brief   HAL MSP module.
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
/** @addtogroup STM32F4xx_HAL_Examples
  * @{
  */

/** @defgroup HAL_MSP
  * @brief HAL MSP module.
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup HAL_MSP_Private_Functions
  * @{
  */


/**
  * @brief TIM MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration
  *           - DMA configuration for transmission request by peripheral
  * @param htim: TIM handle pointer
  * @retval None
  */
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
  GPIO_InitTypeDef   GPIO_InitStruct;
  static DMA_HandleTypeDef  hdma_tim;

  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* TIMx clock enable */
  TIMx_CLK_ENABLE();

  /* Enable GPIO Channel3/3N Clocks */
  TIMx_CHANNEL1_GPIO_CLK_ENABLE();

  /* Enable DMA clock */
  DMAx_CLK_ENABLE();

  /* Configure TIM3_Channel3 in output, push-pull & alternate function mode */
  GPIO_InitStruct.Pin = GPIO_PIN_CHANNEL1;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF_TIMx;
  HAL_GPIO_Init(TIMx_GPIO_CHANNEL1_PORT, &GPIO_InitStruct);


  /* Set the parameters to be configured */
  hdma_tim.Init.Channel = DMA_CHANNEL_3;
  hdma_tim.Init.Direction = DMA_MEMORY_TO_PERIPH;
  hdma_tim.Init.PeriphInc = DMA_PINC_DISABLE;
  hdma_tim.Init.MemInc = DMA_MINC_ENABLE;
  hdma_tim.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD ;
  hdma_tim.Init.MemDataAlignment = DMA_MDATAALIGN_WORD ;
  hdma_tim.Init.Mode = DMA_CIRCULAR;
  hdma_tim.Init.Priority = DMA_PRIORITY_HIGH;
  hdma_tim.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
  //hdma_tim.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
  //hdma_tim.Init.MemBurst = DMA_MBURST_SINGLE;
  //hdma_tim.Init.PeriphBurst = DMA_PBURST_SINGLE;

  /* Set hdma_tim instance */
  hdma_tim.Instance = TIMx_CC1_DMA_INST;

  /* Link hdma_tim to hdma[TIM_DMA_ID_CC3] (channel3) */
  __HAL_LINKDMA(htim, hdma[TIM_DMA_ID_CC1], hdma_tim);

  /* Initialize TIMx DMA handle */
  HAL_DMA_Init(htim->hdma[TIM_DMA_ID_CC1]);

  /*##-2- Configure the NVIC for DMA #########################################*/
  /* NVIC configuration for DMA transfer complete interrupt */
  HAL_NVIC_SetPriority(TIMx_DMA_IRQn, 0, 0);	// Higher priority on DMA
  HAL_NVIC_EnableIRQ(TIMx_DMA_IRQn);
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
  GPIO_InitTypeDef  GPIO_InitStruct;
  if(huart->Instance==USARTx)
  {
  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* Enable GPIO TX/RX clock */
	  USARTx_TX_GPIO_CLK_ENABLE();
	  USARTx_RX_GPIO_CLK_ENABLE();

	  /* Enable USARTx clock */
	  USARTx_CLK_ENABLE();

	  /*##-2- Configure peripheral GPIO ##########################################*/
	  /* UART TX GPIO pin configuration  */
	  GPIO_InitStruct.Pin       = USARTx_TX_PIN;
	  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	  GPIO_InitStruct.Pull      = GPIO_PULLUP;
	  GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
	  GPIO_InitStruct.Alternate = USARTx_TX_AF;

	  HAL_GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStruct);

	  /* UART RX GPIO pin configuration  */
	  GPIO_InitStruct.Pin = USARTx_RX_PIN;
	  GPIO_InitStruct.Alternate = USARTx_RX_AF;

	  HAL_GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStruct);

		HAL_NVIC_EnableIRQ(UARTx_IRQn);
		HAL_NVIC_SetPriority(UARTx_IRQn, 1, 0); // less priority on UART
  }
}

/**
  * @brief UART MSP De-Initialization
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  *          - Revert GPIO and NVIC configuration to their default state
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
	  if(huart->Instance==USARTx)
	  {
	/*##-1- Reset peripherals ##################################################*/
		  USARTx_FORCE_RESET();
		  USARTx_RELEASE_RESET();

  /*##-2- Disable peripherals and GPIO Clocks #################################*/
  /* Configure UART Tx as alternate function  */
		  HAL_GPIO_DeInit(USARTx_TX_GPIO_PORT, USARTx_TX_PIN);
  /* Configure UART Rx as alternate function  */
		  HAL_GPIO_DeInit(USARTx_RX_GPIO_PORT, USARTx_RX_PIN);
	  }
}

/**
  * @brief UART MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration
  * @param huart: UART handle pointer
  * @retval None
  */


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

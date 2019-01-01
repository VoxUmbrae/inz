/**
  ******************************************************************************
  * File Name          : main.h
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2019 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
  /* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define SW1_Pin GPIO_PIN_13
#define SW1_GPIO_Port GPIOC
#define SW1_EXTI_IRQn EXTI15_10_IRQn
#define ADC_Pin GPIO_PIN_4
#define ADC_GPIO_Port GPIOA
#define T_1K_Pin GPIO_PIN_5
#define T_1K_GPIO_Port GPIOA
#define T_100K_Pin GPIO_PIN_6
#define T_100K_GPIO_Port GPIOA
#define T_10K_Pin GPIO_PIN_7
#define T_10K_GPIO_Port GPIOA
#define LCD_D7_Pin GPIO_PIN_0
#define LCD_D7_GPIO_Port GPIOB
#define LCD_D6_Pin GPIO_PIN_1
#define LCD_D6_GPIO_Port GPIOB
#define LCD_D5_Pin GPIO_PIN_2
#define LCD_D5_GPIO_Port GPIOB
#define LCD_D4_Pin GPIO_PIN_10
#define LCD_D4_GPIO_Port GPIOB
#define LCD_D3_Pin GPIO_PIN_11
#define LCD_D3_GPIO_Port GPIOB
#define LCD_D2_Pin GPIO_PIN_12
#define LCD_D2_GPIO_Port GPIOB
#define LCD_D1_Pin GPIO_PIN_13
#define LCD_D1_GPIO_Port GPIOB
#define LCD_D0_Pin GPIO_PIN_14
#define LCD_D0_GPIO_Port GPIOB
#define LCD_E_Pin GPIO_PIN_15
#define LCD_E_GPIO_Port GPIOB
#define LCD_RW_Pin GPIO_PIN_6
#define LCD_RW_GPIO_Port GPIOC
#define LCD_RS_Pin GPIO_PIN_7
#define LCD_RS_GPIO_Port GPIOC
#define Bkonf_Pin GPIO_PIN_8
#define Bkonf_GPIO_Port GPIOA
#define UART_TX_Pin GPIO_PIN_9
#define UART_TX_GPIO_Port GPIOA
#define UART_RX_Pin GPIO_PIN_10
#define UART_RX_GPIO_Port GPIOA
#define BSTATUS1_Pin GPIO_PIN_11
#define BSTATUS1_GPIO_Port GPIOA
#define BSTATUS2_Pin GPIO_PIN_12
#define BSTATUS2_GPIO_Port GPIOA
#define Breset_Pin GPIO_PIN_15
#define Breset_GPIO_Port GPIOA
#define SW2_Pin GPIO_PIN_5
#define SW2_GPIO_Port GPIOB
#define SW2_EXTI_IRQn EXTI9_5_IRQn
#define SW3_Pin GPIO_PIN_6
#define SW3_GPIO_Port GPIOB
#define SW3_EXTI_IRQn EXTI9_5_IRQn
#define SW4_Pin GPIO_PIN_7
#define SW4_GPIO_Port GPIOB
#define SW4_EXTI_IRQn EXTI9_5_IRQn
#define SW5_Pin GPIO_PIN_8
#define SW5_GPIO_Port GPIOB
#define SW5_EXTI_IRQn EXTI9_5_IRQn
#define SW6_Pin GPIO_PIN_9
#define SW6_GPIO_Port GPIOB
#define SW6_EXTI_IRQn EXTI9_5_IRQn

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

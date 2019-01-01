/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32l1xx_hal.h"
#include "fatfs.h"

/* USER CODE BEGIN Includes */
#include "stm32l1xx_hal_liquid_crystal.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc;

SD_HandleTypeDef hsd;
HAL_SD_CardInfoTypedef SDCardInfo;

TIM_HandleTypeDef htim7;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
int pomiarstart=0;
uint8_t guzik=0;
uint8_t menu=1;
uint8_t czaspomiaru=1;
uint8_t progwyzwalania=1;
uint8_t zapis=1;
uint8_t wzmocnienie=2;
uint16_t PomiarADC;
float wynikpomiaru[12];
float wynikpomiaru1[12];
uint8_t i=0;
uint8_t zapiszdo1=0;
int nrprobki;
FATFS myFATFS;
FIL myFile;
UINT myBytes=0;
int test=1;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SDIO_SD_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_ADC_Init(void);
static void MX_TIM7_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SDIO_SD_Init();
  MX_FATFS_Init();
  MX_USART1_UART_Init();
  MX_ADC_Init();
  MX_TIM7_Init();

  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim7);
  HAL_GPIO_WritePin(GPIOA, T_10K_Pin, GPIO_PIN_SET);
  LCD_Init(2, 16);
  LCD_PrintString(1, 1, "Rozpocznij pomiar");
  f_mount(&myFATFS,SD_Path,1);
/*
  char fileName[] = "TEST.txt\0";
  int a=99,b=99,c=99;
  a=f_mount(&myFATFS,SD_Path,1);
  if(a==0)
  	  {

	  b=f_open(&myFile, fileName, FA_WRITE | FA_CREATE_ALWAYS);
  	  if(b==0)
  	  	  {
  		  char myData[] = "test";
  		  c=f_write(&myFile, myData,sizeof(myData),&myBytes);
  		  f_close(&myFile);
  	  	  }
  	  }

  LCD_PrintString(1, 1, "B��dy:");
  LCD_PrintNumber(2,1,a);
  LCD_PrintNumber(2,5,b);
  LCD_PrintNumber(2,9,c);*/



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */


	  if(pomiarstart==1)
	  {
			  LCD_PrintString(1, 1, "Trwa pomiar       ");
			  LCD_PrintString(2, 1, "                  ");
			  char fileName[] = "TEST.txt\0";
			  if(f_open(&myFile, fileName, FA_WRITE | FA_CREATE_ALWAYS)==FR_OK)
			  {
				  while(nrprobki<5000)
				  {
					  if(i==12)
					  {
						  if(zapiszdo1==1)
						  {
							  zapiszdo1=0;
				  		  	  f_write(&myFile, wynikpomiaru,sizeof(wynikpomiaru),&myBytes);
				  			  if(test==1)
				  			  {
				  				  LCD_PrintString(1, 1, "Tu jestem       ");
				  				  test=0;
				  			  }
						  }
						  else
						  {
							  zapiszdo1=1;
			  		  		  f_write(&myFile, wynikpomiaru1,sizeof(wynikpomiaru1),&myBytes);
						  }
						  i=0;
					  }
				  }
		  		 f_close(&myFile);
			  }
			  LCD_PrintString(1, 1, "Pomiar zakonczony");
			  pomiarstart=0;
		  }


	  }
  /* USER CODE BEGIN 3 */


  /* USER CODE END 3 */
}


/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE
                              |RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_5;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL4;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLL_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* ADC init function */
static void MX_ADC_Init(void)
{

  ADC_ChannelConfTypeDef sConfig;

    /**Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) 
    */
  hadc.Instance = ADC1;
  hadc.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc.Init.Resolution = ADC_RESOLUTION_12B;
  hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc.Init.EOCSelection = ADC_EOC_SEQ_CONV;
  hadc.Init.LowPowerAutoWait = ADC_AUTOWAIT_DISABLE;
  hadc.Init.LowPowerAutoPowerOff = ADC_AUTOPOWEROFF_DISABLE;
  hadc.Init.ChannelsBank = ADC_CHANNELS_BANK_A;
  hadc.Init.ContinuousConvMode = DISABLE;
  hadc.Init.NbrOfConversion = 1;
  hadc.Init.DiscontinuousConvMode = DISABLE;
  hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc.Init.DMAContinuousRequests = DISABLE;
  if (HAL_ADC_Init(&hadc) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
    */
  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_4CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* SDIO init function */
static void MX_SDIO_SD_Init(void)
{

  hsd.Instance = SDIO;
  hsd.Init.ClockEdge = SDIO_CLOCK_EDGE_RISING;
  hsd.Init.ClockBypass = SDIO_CLOCK_BYPASS_DISABLE;
  hsd.Init.ClockPowerSave = SDIO_CLOCK_POWER_SAVE_DISABLE;
  hsd.Init.BusWide = SDIO_BUS_WIDE_1B;
  hsd.Init.HardwareFlowControl = SDIO_HARDWARE_FLOW_CONTROL_DISABLE;
  hsd.Init.ClockDiv = 16;

}

/* TIM7 init function */
static void MX_TIM7_Init(void)
{

  TIM_MasterConfigTypeDef sMasterConfig;

  htim7.Instance = TIM7;
  htim7.Init.Prescaler = 2096;
  htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim7.Init.Period = 999;
  if (HAL_TIM_Base_Init(&htim7) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* USART1 init function */
static void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, T_1K_Pin|T_100K_Pin|T_10K_Pin|Bkonf_Pin 
                          |Breset_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LCD_D7_Pin|LCD_D6_Pin|LCD_D5_Pin|LCD_D4_Pin 
                          |LCD_D3_Pin|LCD_D2_Pin|LCD_D1_Pin|LCD_D0_Pin 
                          |LCD_E_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, LCD_RW_Pin|LCD_RS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : SW1_Pin */
  GPIO_InitStruct.Pin = SW1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(SW1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : T_1K_Pin T_100K_Pin T_10K_Pin Bkonf_Pin 
                           Breset_Pin */
  GPIO_InitStruct.Pin = T_1K_Pin|T_100K_Pin|T_10K_Pin|Bkonf_Pin 
                          |Breset_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_D7_Pin LCD_D6_Pin LCD_D5_Pin LCD_D4_Pin 
                           LCD_D3_Pin LCD_D2_Pin LCD_D1_Pin LCD_D0_Pin 
                           LCD_E_Pin */
  GPIO_InitStruct.Pin = LCD_D7_Pin|LCD_D6_Pin|LCD_D5_Pin|LCD_D4_Pin 
                          |LCD_D3_Pin|LCD_D2_Pin|LCD_D1_Pin|LCD_D0_Pin 
                          |LCD_E_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_RW_Pin LCD_RS_Pin */
  GPIO_InitStruct.Pin = LCD_RW_Pin|LCD_RS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : BSTATUS1_Pin BSTATUS2_Pin */
  GPIO_InitStruct.Pin = BSTATUS1_Pin|BSTATUS2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SW2_Pin SW3_Pin SW4_Pin SW5_Pin 
                           SW6_Pin */
  GPIO_InitStruct.Pin = SW2_Pin|SW3_Pin|SW4_Pin|SW5_Pin 
                          |SW6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	 if(GPIO_Pin == SW1_Pin){
		 guzik=1;
		 // LCD_PrintNumber(1, 1, guzik);
	 }
	 else if(GPIO_Pin == SW2_Pin)
	 {
		 guzik=2;
		  //LCD_PrintString(1, 1, "SW2 ");
	 }
	 else if(GPIO_Pin == SW3_Pin)
	 {
		 guzik=3;
		  //LCD_PrintString(1, 1, "SW3 ");
	 }
	 else if(GPIO_Pin == SW4_Pin)
	 {
		 guzik=4;
		  //LCD_PrintString(1, 1, "SW4 ");
	 }
	 else if(GPIO_Pin == SW5_Pin)
	 {
		 guzik=5;
		  //LCD_PrintString(1, 1, "SW5 ");
	 }
	 else if(GPIO_Pin == SW6_Pin)
	 {
		 guzik=6;
		 // LCD_PrintString(1, 1, "SW6 ");
	 }


	 switch(menu){
	 case 1: //Rozpocznij pomiar
		 switch (guzik){
		 	 case 1:
		 	 case 2:
		 		 menu=2; //ustaw parametry pomiaru
			 		LCD_PrintString(1, 1,"                  )");
			 		LCD_PrintString(2, 1,"                  )");
		 		LCD_PrintString(1, 1, "Ustaw parametry pomiaru");
		 	 break;
		 	 case 5:
		 		pomiarstart=1;
		 	 break;
		 	 case 3:
		 	 case 4:
		 	 case 6:
		 	break; //nie rob nic
		 	 }
		 break;
	 case 2://Ustaw parametry pomiaru
		 switch (guzik){
		 	 case 1:
		 	 case 2:
		 		 menu=1;//rozpocznij pomiar
			 		LCD_PrintString(1, 1,"                  )");
			 		LCD_PrintString(2, 1,"                  )");
			 	LCD_PrintString(1, 1, "Rozpocznij pomiar");
		 		 break;
		 	 case 3:
		 	 case 4:
		 	 case 6:
		 		 break;// nie rob nic
		 	 case 5:
		 		 menu=3;//Spos�b pomiaru
			 		LCD_PrintString(1, 1,"                  )");
			 		LCD_PrintString(2, 1,"                  )");
		 		LCD_PrintString(1, 1, "Tryb pomiaru:"); //od nacisniecia guzika czy wyzwalany
		 		LCD_PrintString(2, 1, "wyzw. napieciem"); //od nacisniecia guzika czy wyzwalany
		 		break;
		 	 }
		 break;
	 case 3:
		 switch (guzik){
		 	 case 1:
		 	 case 2:
		 	break;//nie rob nic
		 	 case 3:
		 		 menu=2; //ustaw parametry pomiaru
			 		LCD_PrintString(1, 1,"                  )");
			 		LCD_PrintString(2, 1,"                  )");
		 		LCD_PrintString(1, 1, "Ustaw parametry pomiaru");
		 	break;
		 	 case 4:
		 	 case 6:
		 		 menu=4;//wyzwalany przyciskiem
			 		LCD_PrintString(1, 1,"                  )");
			 		LCD_PrintString(2, 1,"                  )");
		 		LCD_PrintString(1, 1, "Tryb pomiaru:");
		 		LCD_PrintString(2, 1, "wyzw. przyciskiem"); //od nacisniecia guzika czy wyzwalany
		 	 break;
		 	 case 5:
		 		 menu=5;//ustawiamy czas trwania pomiaru
			 		LCD_PrintString(1, 1,"                  )");
			 		LCD_PrintString(2, 1,"                  )");
		 		LCD_PrintString(1, 1, "Czas trwania pomiaru:");
		 		LCD_PrintNumber(2,1,czaspomiaru);
		 	 break;
		 		}
		 break;
		 case 4:
			 switch (guzik){
			 	 case 1:
			 	 case 2:
			 	break;//nie rob nic
			 	 case 3:
			 		 menu=2; //ustaw parametry pomiaru
				 		LCD_PrintString(1, 1,"                  )");
				 		LCD_PrintString(2, 1,"                  )");
			 		LCD_PrintString(1, 1, "Ustaw parametry pomiaru");
			 	break;
			 	 case 4:
			 	 case 6:
			 		 menu=3;//wyzwalany przyciskiem
				 		LCD_PrintString(1, 1,"                  )");
				 		LCD_PrintString(2, 1,"                  )");
			 		LCD_PrintString(1, 1, "Tryb pomiaru:");
			 		LCD_PrintString(2, 1, "wyzw. napieciem"); //od nacisniecia guzika czy wyzwalany
			 	 break;
			 	 case 5:
			 		 menu=5;//ustawiamy czas trwania pomiaru
				 		LCD_PrintString(1, 1,"                  )");
				 		LCD_PrintString(2, 1,"                  )");
			 		LCD_PrintString(1, 1, "Czas trwania pomiaru:");
			 		LCD_PrintNumber(2,1,czaspomiaru);
			 	 break;
			 		}
			 break;
			 case 5:
				 switch (guzik){
				 	 case 1:
				 		 menu=7;
					 		LCD_PrintString(1, 1,"                  )");
					 		LCD_PrintString(2, 1,"                  )");
				 		LCD_PrintString(1, 1, "Prog wyzwalania");
				 		LCD_PrintNumber(2,1,progwyzwalania);
				 		 break;
				 	 case 2:
				 		 menu=6;
					 		LCD_PrintString(1, 1,"                  )");
					 		LCD_PrintString(2, 1,"                  )");
				 		LCD_PrintString(1, 1, "Gdzie zapisac");
				 		LCD_PrintNumber(2,1,zapis);
				 	break;
				 	 case 3:
				 		 menu=3;
					 		LCD_PrintString(1, 1,"                  )");
					 		LCD_PrintString(2, 1,"                  )");
					 	LCD_PrintString(1, 1, "Tryb pomiaru:"); //od nacisniecia guzika czy wyzwalany
					 	LCD_PrintString(2, 1, "wyzw. napieciem"); //od nacisniecia guzika czy wyzwalany
					 	break;
				 	 case 4:
				 		 czaspomiaru++;
				 		 if(czaspomiaru==16){czaspomiaru=1;}
				 		 	LCD_PrintString(1, 1,"                  )");
					 		LCD_PrintString(2, 1,"                  )");
					 		LCD_PrintString(1, 1, "Czas trwania pomiaru:");
					 		LCD_PrintNumber(2,1,czaspomiaru);
					 		break;
				 	 case 6:
				 		 czaspomiaru--;
				 		if(czaspomiaru==0){czaspomiaru=15;}
				 		LCD_PrintString(1, 1,"                  )");
				 		LCD_PrintString(2, 1,"                  )");
				 		LCD_PrintString(1, 1, "Czas trwania pomiaru:");
					 		LCD_PrintNumber(2,1,czaspomiaru);
				 		 break;
				 	 case 5:
				 		 menu=1;
					 		LCD_PrintString(1, 1,"                  )");
					 		LCD_PrintString(2, 1,"                  )");
				 		LCD_PrintString(1, 1, "Rozpocznij pomiar");
				 	 break;
				 }
				 break;
				case 6:
					switch (guzik){
						 case 1:
							 menu=5;
						 		LCD_PrintString(1, 1,"                  )");
						 		LCD_PrintString(2, 1,"                  )");
						 		LCD_PrintString(1, 1, "Czas trwania pomiaru:");
						 		LCD_PrintNumber(2,1,czaspomiaru);
						 	break;
						 case 2:
						 	 menu=7;
						 		LCD_PrintString(1, 1,"                  )");
						 		LCD_PrintString(2, 1,"                  )");
						 		LCD_PrintString(1, 1, "Prog wyzwalania");
						 		LCD_PrintNumber(2,1,progwyzwalania);
						 break;
						 case 3:
							 menu=3;
						 		LCD_PrintString(1, 1,"                  )");
						 		LCD_PrintString(2, 1,"                  )");
							 LCD_PrintString(1, 1, "Tryb pomiaru:"); //od nacisniecia guzika czy wyzwalany
							 LCD_PrintString(2, 1, "wyzw. napieciem"); //od nacisniecia guzika czy wyzwalany
							 break;
						  case 4:
						 	 zapis++;
						 	 if(zapis==4){zapis=1;}
						 	 	 LCD_PrintString(1, 1,"                  )");
						 		LCD_PrintString(2, 1,"                  )");
						 		LCD_PrintString(1, 1, "Gdzie zapisac");
							LCD_PrintNumber(2,1,zapis);
							break;
						  case 6:
							  zapis--;
						 	if(zapis==0){zapis=3;}
						 	LCD_PrintString(1, 1,"                  )");
					 		LCD_PrintString(2, 1,"                  )");
					 		LCD_PrintString(1, 1, "Gdzie zapisac");
								LCD_PrintNumber(2,1,zapis);
						 	 break;
						  case 5:
						 	 menu=1;
						 		LCD_PrintString(1, 1,"                  )");
						 		LCD_PrintString(2, 1,"                  )");
						 	LCD_PrintString(1, 1, "Rozpocznij pomiar");
						 	 break;
				 		}
					break;
				case 7:
					switch (guzik){
						case 1:
					 		 menu=6;
					 		LCD_PrintString(1, 1,"                  )");
					 		LCD_PrintString(2, 1,"                  )");
					 		LCD_PrintString(1, 1, "Gdzie zapisac");
					 		LCD_PrintNumber(2,1,zapis);
							break;
						 case 2:
							 menu=5;
						 		LCD_PrintString(1, 1,"                  )");
						 		LCD_PrintString(2, 1,"                  )");
						 		LCD_PrintString(1, 1, "Czas trwania pomiaru:");
						 		LCD_PrintNumber(2,1,czaspomiaru);
						 break;
						 case 3:
							 menu=3;
						 		LCD_PrintString(1, 1,"                  )");
						 		LCD_PrintString(2, 1,"                  )");
							LCD_PrintString(1, 1, "Tryb pomiaru:"); //od nacisniecia guzika czy wyzwalany
							LCD_PrintString(2, 1, "pomiar wyzwalany napieciem"); //od nacisniecia guzika czy wyzwalany
							 break;
						case 4:
							progwyzwalania++;
							 if(progwyzwalania==6){progwyzwalania=1;}
							 LCD_PrintString(1, 1,"                  )");
						 		LCD_PrintString(2, 1,"                  )");
						 		LCD_PrintString(1, 1, "Prog wyzwalania");
							 LCD_PrintNumber(2,1,progwyzwalania);
							break;
						case 6:

							progwyzwalania--;
							if(progwyzwalania==0){progwyzwalania=5;}
							LCD_PrintString(1, 1,"                  )");
					 		LCD_PrintString(2, 1,"                  )");
					 		LCD_PrintString(1, 1, "Prog wyzwalania");
							LCD_PrintNumber(2,1,progwyzwalania);
							 break;
						case 5:
							 menu=1;
						 		LCD_PrintString(1, 1,"                  )");
						 		LCD_PrintString(2, 1,"                  )");
							LCD_PrintString(1, 1, "Rozpocznij pomiar");
							 break;
					 		}

	 }

}
/*
void rozpocznijpomiar()
{

	  char fileName[] = "TEST.txt\0";
	  	  if(f_open(&myFile, fileName, FA_WRITE | FA_CREATE_ALWAYS)==FR_OK)
	  	  	  {
	  		  HAL_ADC_Start(&hadc);
	  		  int i=0;
	  		  while (i<40000)
	  		  	  {
	  			  if (HAL_ADC_PollForConversion(&hadc, 10) == HAL_OK) // Oczekiwanie na zakonczenie konwersji
	  			  	  {
	  				  PomiarADC = HAL_ADC_GetValue(&hadc);// Pobranie zmierzonej wartosci
	  				  wynikpomiaru = (3.3*PomiarADC)/4095;// Przeliczenie wartosci zmierzonej na napiecie
	  				  LCD_PrintString(1, 1, "Obecny wynik:");
	  				  LCD_PrintNumber(2,1,PomiarADC);
	  				  LCD_PrintFloat(2,7,wynikpomiaru,4);

	  		  		char myData[12];
	  				sprintf(myData, "%d;%d", i,PomiarADC);

	  		  		  f_write(&myFile, myData,sizeof(myData),&myBytes);


	  				  HAL_ADC_Start(&hadc);// Rozpoczecie nowej konwersji
	  			  	  }
	  		  	  }
	  		  f_close(&myFile);
	  	  	  }

		  LCD_PrintString(1, 1, "Pomiar zakonczony");


}*/


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
 if(htim->Instance == TIM7 && pomiarstart==1){ // Je�eli przerwanie pochodzi od timera 7
	 	 HAL_ADC_Start(&hadc);
	 	 PomiarADC = HAL_ADC_GetValue(&hadc);// Pobranie zmierzonej wartosci
	 	 if(zapiszdo1==0)
	 	 {
	 	 wynikpomiaru[i] = (3.3*PomiarADC)/4095;// Przeliczenie wartosci zmierzonej na napiecie
	 	 }
	 	 else
	 	 {
	 	 wynikpomiaru1[i] = (3.3*PomiarADC)/4095;
	 	 }
	 	 i++;
	 	 nrprobki++;

 }
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

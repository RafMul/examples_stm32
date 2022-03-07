/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "string.h"
#include "dht11_sensor.h"
#include "buffer_ring.h"
#include "parse_data.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define timer   			2000
#define timer1 				6000
#define timer2 				100000

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
uint8_t welcome_user[] = "USART is ready ";
uint8_t temp[40];
uint8_t tempData[30] ;

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
BufferRing_t ReciveBuffer;
uint8_t ReciveTemp;
uint8_t RecivedLine;
uint8_t ReceviedData[30];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */




/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
DHT_DataTypedef DHT11_Data;
float Temperature, Humidity;
void temper(void);
void humidity(void);
void Uart_Message(char* Message);

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */



  /* USER CODE END 1 */


  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */

	HAL_Init();
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();
  /* USER CODE BEGIN SysInit */

	uint32_t start = HAL_GetTick();
	// uint32_t start1 = HAL_GetTick();
	//uint32_t start2 = HAL_GetTick();






  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_DMA_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */

  HAL_UART_Transmit_IT(&huart2, welcome_user ,sizeof(welcome_user) );
  HAL_UART_Receive_IT(&huart2, &ReciveTemp, 1);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */


	  if (HAL_GetTick() - start > timer) {
			start = HAL_GetTick();
			HAL_GPIO_TogglePin(GPIOA, LD2_Pin);

			//temper();
		}
		/*
		 if (HAL_GetTick()-start1 >timer1)
		 {
		 start1 = HAL_GetTick();
		 HAL_GPIO_TogglePin(GPIOA, LD_out_Pin)	;
		 //humidity();
		 }
		 */

		if (RecivedLine > 0) {

			Parse_SaveLine(&ReciveBuffer, ReceviedData);
			RecivedLine--;

			Parse_Data(ReceviedData);

		}
		/*
		 if (HAL_GetTick()-start2 >timer2)
		 {
		 start2 = HAL_GetTick();

		 }

		 */


  /* USER CODE END 3 */
  }
}
/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
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
}

/* USER CODE BEGIN 4 */


void temper(void) {

	uint8_t size;
	DHT_GetData(&DHT11_Data);
	Temperature = DHT11_Data.Temperature;
	Humidity = DHT11_Data.Humidity;
	//HAL_Delay(3000);
	size = sprintf((char*) tempData, "Temperature is %.0f", Temperature);
	HAL_UART_Transmit(&huart2, tempData, size, 500);

}
void humidity(void){

	//uint8_t i;
	DHT_GetData(&DHT11_Data);
	Humidity = DHT11_Data.Humidity;
	sprintf((char*) tempData, " Humidity is %.0f", Humidity);

	//BR_Write(&ReciveBuffer, Humidity);
	HAL_UART_Transmit_IT(&huart2, &ReciveTemp, sizeof(ReciveBuffer));

}



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {

	if (huart->Instance == USART2) {

		//BR_Write(&ReciveBuffer, ReciveTemp);

		if (RB_STATE_OK == BR_Write(&ReciveBuffer, ReciveTemp)) {
			if (ReciveTemp == ENDLINE) {
				RecivedLine++;
			}

		}
		HAL_UART_Receive_IT(&huart2, &ReciveTemp, 1);
	}
}



/*
void HAL_UART_TxHalfCpltCallback(UART_HandleTypeDef *huart)
{
   uint8_t Wyswietl[30];
   uint16_t size = 0;


   switch(Received)
   {
   case '0':
   {
       size = sprintf((char*)Wyswietl, "Wylaczenie wszystkich diod\n\r");
       HAL_GPIO_TogglePin(GPIOA, LD_out_Pin)	;
       HAL_GPIO_WritePin(GPIOA, LD_out_Pin, GPIO_PIN_RESET);
     HAL_GPIO_WritePin(GPIOA, LD2_Pin, GPIO_PIN_RESET);

       break;
   }
   case '1':
   {
       size = sprintf((char*)Wyswietl, "Swieci dioda zielona: \n\r");
       HAL_GPIO_WritePin(GPIOA, LD_out_Pin, GPIO_PIN_SET);
       break;
   }

   case '2':
   {
       size = sprintf((char*)Wyswietl, "Swieci dioda pomaranczowa: \n\r");
       //HAL_GPIO_WritePin(GPIOA, LD2_Pin, GPIO_PIN_SET);
       break;
   }
   case '3':
   {
       size = sprintf((char*)Wyswietl, "Swieci dioda czerwona: \n\r");
       //HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
       break;
   }

   case '4':
   {
       size = sprintf((char*)Wyswietl, "Swieci dioda niebieska: \n\r");
      // HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
       break;
   }

   default:
   {
       size = sprintf((char*)Wyswietl, "Odebrano zly znak: '%c'\n\r", Received);
       break;
   }
   }


   HAL_UART_Transmit_IT(&huart2, Wyswietl, size);

   HAL_UART_Receive_IT(&huart2, &Received, 1);
}
*/

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */


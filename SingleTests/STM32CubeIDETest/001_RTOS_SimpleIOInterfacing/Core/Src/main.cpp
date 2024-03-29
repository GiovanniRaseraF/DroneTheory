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
#include "cmsis_os.h"
#include "usart.h"
#include "gpio.h"
#include <vector>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void blink_green_led(void *pvParameters)
{
	TickType_t TaskTimeStamp;
	TaskTimeStamp = xTaskGetTickCount();

	for(;;){
		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		vTaskDelayUntil(&TaskTimeStamp, 500);
	}
}

void blink_red_led(void *pvParameters)
{
	TickType_t TaskTimeStamp;
	TaskTimeStamp = xTaskGetTickCount();

	for(;;){
		HAL_GPIO_TogglePin(LDred_GPIO_Port, LDred_Pin);
		vTaskDelayUntil(&TaskTimeStamp, 100);
	}
}

void periodic_prime_compute(void *pvParameters){
	std::vector<int> v;
	v.push_back(2);
	int current = 3;

	for(;;){
		bool prime = true;
		HAL_GPIO_WritePin(LDred_GPIO_Port, LDred_Pin, GPIO_PIN_RESET);

		for(auto p : v){
			if(current % p == 0)
				prime = false;
		}

		if(prime){
			v.push_back(current);
			//blink
			HAL_GPIO_WritePin(LDred_GPIO_Port, LDred_Pin, GPIO_PIN_RESET);
			HAL_GPIO_TogglePin(LDred_GPIO_Port, LDred_Pin);
			vTaskDelay(300);
			HAL_GPIO_TogglePin(LDred_GPIO_Port, LDred_Pin);
		}

		current += 2;
	}
}

void periodic_prime_compute_1(void *pvParameters){
	std::vector<int> v;
	v.push_back(2);
	int current = 3;

	for(;;){
		bool prime = true;

		for(auto p : v){
			if(current % p == 0)
				prime = false;
		}

		if(prime){
			v.push_back(current);
		}

		current += 2;
	}
}

void periodic_prime_compute_2(void *pvParameters){
	std::vector<int> v;
	v.push_back(2);
	int current = 3;

	for(;;){
		bool prime = true;

		for(auto p : v){
			if(current % p == 0)
				prime = false;
		}

		if(prime){
			v.push_back(current);
		}

		current += 2;
	}
}

void periodic_prime_compute_3(void *pvParameters){
	std::vector<int> v;
	v.push_back(2);
	int current = 3;

	for(;;){
		bool prime = true;

		for(auto p : v){
			if(current % p == 0)
				prime = false;
		}

		if(prime){
			v.push_back(current);
		}

		current += 2;
	}
}
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

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  //HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
  TaskHandle_t xHandle_green_led = NULL;
  TaskHandle_t xHandle_red_led = NULL;
  TaskHandle_t xHandle_1 = NULL;
  TaskHandle_t xHandle_2 = NULL;

  BaseType_t xReturned = xTaskCreate(blink_green_led, "blink green", 200, (void *)1, 4, &xHandle_green_led);
  // task created PERIODIC
  if (xReturned == pdPASS);else;

  xReturned = xTaskCreate(periodic_prime_compute, "prime", 200, (void *)1, 3, &xHandle_red_led);
  // second task created PERIODIC
  if (xReturned == pdPASS);else;

  xReturned = xTaskCreate(periodic_prime_compute_1, "prime_1", 200, (void *)1, 1, &xHandle_1);
  // second task created PERIODIC
  if (xReturned == pdPASS);else;

  xReturned = xTaskCreate(periodic_prime_compute_2, "prime_2", 200, (void *)1, 1, &xHandle_2);
  // second task created PERIODIC
  if (xReturned == pdPASS);else;

  /* USER CODE END 2 */

  /* Call init function for freertos objects (in freertos.c) */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 50;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

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

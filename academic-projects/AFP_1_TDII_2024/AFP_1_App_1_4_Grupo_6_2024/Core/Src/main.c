/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "string.h"

/* Private variables ---------------------------------------------------------*/
ETH_TxPacketConfig TxConfig;
ETH_DMADescTypeDef  DMARxDscrTab[ETH_RX_DESC_CNT]; /* Ethernet Rx DMA Descriptors */
ETH_DMADescTypeDef  DMATxDscrTab[ETH_TX_DESC_CNT]; /* Ethernet Tx DMA Descriptors */

ETH_HandleTypeDef heth;
UART_HandleTypeDef huart3;
PCD_HandleTypeDef hpcd_USB_OTG_FS;

/* USER CODE BEGIN PV */
// Vector de LEDs
GPIO_TypeDef* LED_PORTS[] = {GPIOB, GPIOB, GPIOB};
uint16_t LED_PINS[] = {GPIO_PIN_0, GPIO_PIN_7, GPIO_PIN_14};
int num_leds = 3;

uint8_t button_state = 0;
uint8_t last_button_state = 0;

// Tiempos de alternancia
int times[] = {100, 250, 500, 1000};
int current_time_index = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);  // Aseguramos la función de inicialización GPIO

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

int main(void)
{
  /* MCU Configuration--------------------------------------------------------*/
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();

  /* Prueba de Encendido de LEDs */
  for (int i = 0; i < num_leds; i++) {
      HAL_GPIO_WritePin(LED_PORTS[i], LED_PINS[i], GPIO_PIN_SET);
  }
  HAL_Delay(1000);  // Encender los LEDs por 1 segundo para probar
  for (int i = 0; i < num_leds; i++) {
      HAL_GPIO_WritePin(LED_PORTS[i], LED_PINS[i], GPIO_PIN_RESET);
  }

  while (1)
  {
      // Leer el estado del pulsador
      button_state = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);

      // Detectar el flanco de subida (cambio de estado de 0 a 1)
      if (button_state == GPIO_PIN_SET && last_button_state == GPIO_PIN_RESET)
      {
          current_time_index = (current_time_index + 1) % 4; // Cambiar a la siguiente frecuencia
      }

      last_button_state = button_state; // Actualizar el estado del pulsador

      // Encender los LEDs
      for (int i = 0; i < num_leds; i++) {
          HAL_GPIO_WritePin(LED_PORTS[i], LED_PINS[i], GPIO_PIN_SET);
      }
      HAL_Delay(times[current_time_index]);

      // Apagar los LEDs
      for (int i = 0; i < num_leds; i++) {
          HAL_GPIO_WritePin(LED_PORTS[i], LED_PINS[i], GPIO_PIN_RESET);
      }
      HAL_Delay(times[current_time_index]);
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_7|GPIO_PIN_14, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 (Botón de usuario) */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB7 PB14 (LEDs) */
  GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_7 | GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
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

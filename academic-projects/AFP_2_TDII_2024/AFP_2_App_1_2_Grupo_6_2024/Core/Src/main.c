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
#include "API_GPIO.h"  // Se incluye el driver GPIO
#include "string.h"

/* Private variables ---------------------------------------------------------*/
ETH_HandleTypeDef heth;
UART_HandleTypeDef huart3;
PCD_HandleTypeDef hpcd_USB_OTG_FS;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PV */
int direction = 1;  // 1 para adelante, -1 para atrÃ¡s
int current_led = 0;
uint8_t button_state = 0;
uint8_t last_button_state = 0;
int num_leds = 3;
/* USER CODE END PV */

int main(void)
{
  /* MCU Configuration--------------------------------------------------------*/
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();  // InicializaciÃ³n de GPIO usando el driver

  while (1)
  {
    /* Leer el estado del pulsador */
    button_state = readButton_GPIO();

    /* Detectar el flanco de subida (cambio de estado de 0 a 1) */
    if (button_state && !last_button_state)
    {
      direction = -direction;  // Invertir la direcciÃ³n
    }

    last_button_state = button_state;  // Actualizar el estado del pulsador

    /* Control de los LEDs */
    if (current_led == 0) {
      LED_On(LD1);  // Enciende LED verde
      LED_Off(LD2);  // Apaga LED azul
      LED_Off(LD3);  // Apaga LED rojo
    } else if (current_led == 1) {
      LED_Off(LD1);  // Apaga LED verde
      LED_On(LD2);   // Enciende LED azul
      LED_Off(LD3);  // Apaga LED rojo
    } else if (current_led == 2) {
      LED_Off(LD1);  // Apaga LED verde
      LED_Off(LD2);  // Apaga LED azul
      LED_On(LD3);   // Enciende LED rojo
    }

    HAL_Delay(200);  // Espera de 200 ms

    /* Pasar al siguiente LED basado en la direcciÃ³n */
    current_led = (current_led + direction + num_leds) % num_leds;
  }
}

/* System Clock Configuration */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	  /** Configure the main internal regulator output voltage
	  */
	  __HAL_RCC_PWR_CLK_ENABLE();
	  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	  /** Initializes the RCC Oscillators according to the specified parameters
	  * in the RCC_OscInitTypeDef structure.
	  */
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

	  /** Initializes the CPU, AHB and APB buses clocks
	  */
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

/* GPIO Initialization */
/*void MX_GPIO_Init(void)
{

}

Error Handler */
void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}

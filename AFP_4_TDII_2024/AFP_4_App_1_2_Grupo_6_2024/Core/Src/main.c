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
#include "API_GPIO.h"
#include "API_Delay.h"
#include "string.h"
#include "API_Debounce.h"

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
int direction = 1;  // 1 para adelante, -1 para atrás
int current_led = 0;
uint8_t button_state = 0;
uint8_t last_button_state = 0;
int num_leds = 3;
delay_t led_delay;  // Estructura para el delay de los LEDs

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Error_Handler(void);

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* MCU Configuration--------------------------------------------------------*/
  HAL_Init();
  SystemClock_Config();

  /* Initialize GPIO */
  MX_GPIO_Init();  // Esta función está definida en API_GPIO.h

  // Inicializar el delay con 200ms
  delayInit(&led_delay, 200);
  debounceFSM_init();

  while (1)
  {
	  debounceFSM_update();

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
    /* Verificar si ha pasado el tiempo del delay */
      	        	    if (delayRead(&led_delay)) {
      	        	      /* Pasar al siguiente LED basado en la dirección */
      	        	      current_led = (current_led + direction + num_leds) % num_leds;
      	        	    }
    // // Verificar si se presionó el botón usando readKey()
  	        if (readKey())
  	        {
  	        	direction = -direction;
  	            // Reiniciar las variables de inicializaciÃ³n al cambiar de secuencia
  	            for (int i = 0; i < num_leds; i++) {
  	                        LED_Off((led_T)i);
  	                    }
  	        }


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

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
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

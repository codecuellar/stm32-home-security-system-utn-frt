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
  * La app iniciara con la
secuencia 1 hasta que se presione el pulsador y pase a la secuencia 2, luego de presionar
de nuevo el pulsador pasara a la secuencia 3 y as´ı, sucesivamente, hasta la secuencia
4 para volver a comenzar con la secuencia 1. Descripci´on de las secuencias:
Secuencia 1: idem App 1.1 con una alternancia de 150 ms.
Secuencia 2: hace parpadear los tres leds simult´aneamente con una alternancia
de 300 ms.
Secuencia 3: hace parpadear el LED1 con una alternancia de 100 ms, el LED2
con una alternancia de 300 ms y el led3 con una alternancia de 600 ms.
Secuencia 4: Hace parpadear simult´aneamente LED1 y LED3, mientras que
LED2 lo har´a de manera inversa, con una alternancia de 150 ms. Mientras LED1
y LED3 est´an encendidos, LED2 estara apagado y luego a la inversa.
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "API_GPIO.h"  // Incluyo el driver GPIO
#include "string.h"
#include "API_delay.h"
#include "API_Debounce.h" // Driver Antirrebote

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

ETH_TxPacketConfig TxConfig;
ETH_DMADescTypeDef  DMARxDscrTab[ETH_RX_DESC_CNT]; /* Ethernet Rx DMA Descriptors */
ETH_DMADescTypeDef  DMATxDscrTab[ETH_TX_DESC_CNT]; /* Ethernet Tx DMA Descriptors */

ETH_HandleTypeDef heth;

UART_HandleTypeDef huart3;

PCD_HandleTypeDef hpcd_USB_OTG_FS;

/* USER CODE BEGIN PV */
// Vector de LEDs y tiempos de alternancia
GPIO_TypeDef* LED_PORTS[] = {GPIOB, GPIOB, GPIOB};
uint16_t LED_PINS[] = {GPIO_PIN_0, GPIO_PIN_7, GPIO_PIN_14};
int num_leds = 3;
int direction = 1; // 1 para adelante, -1 para atras
uint8_t button_state = 0;
uint8_t last_button_state = 0;
int sequence = 0; // Secuencia actual (0 a 3)

delay_t delay_led1;
delay_t delay_led2;
delay_t delay_led3;
delay_t delay_sequence;
int current_led = 0;  // Para controlar que LED esta activo en la secuencia 1

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_GPIO_Init(void);
static void MX_ETH_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_USB_OTG_FS_PCD_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* Funcion para secuencia 1 */
void Secuencia1() {
	static bool init_delay = false;

	if (!init_delay) {
	        delayInit(&delay_sequence, 150);
	        init_delay = true;
	    }

	    if (delayRead(&delay_sequence)) {
	        LED_Off((led_T)current_led);
	        current_led = (current_led + 1) % num_leds;
	        LED_On((led_T)current_led);
	    }
}
/* Funcion para secuencia 2 */
void Secuencia2() {
	static bool init_delay = false;
	    static bool leds_on = false;

	    if (!init_delay) {
	        delayInit(&delay_sequence, 300);
	        init_delay = true;
	    }

	    if (delayRead(&delay_sequence)) {
	        if (leds_on) {
	            for (int i = 0; i < num_leds; i++) {
	                LED_Off((led_T)i);
	            }
	        } else {
	            for (int i = 0; i < num_leds; i++) {
	                LED_On((led_T)i);
	            }
	        }
	        leds_on = !leds_on;
	    }
}
/* Funcion para secuencia 3 */
void Secuencia3() {

	static bool init_delays = false;

	    if (!init_delays) {
	        delayInit(&delay_led1, 100);
	        delayInit(&delay_led2, 300);
	        delayInit(&delay_led3, 600);
	        init_delays = true;
	    }

	    if (delayRead(&delay_led1)) {
	        LED_Toggle(LD1);
	    }

	    if (delayRead(&delay_led2)) {
	        LED_Toggle(LD2);
	    }

	    if (delayRead(&delay_led3)) {
	        LED_Toggle(LD3);
	    }

}

/* Funcion para secuencia 4 */
void Secuencia4() {
	static bool init_delay = false;
	    static bool state = false;

	    if (!init_delay) {
	        delayInit(&delay_sequence, 150);
	        init_delay = true;
	    }

	    if (delayRead(&delay_sequence)) {
	        if (state) {
	            LED_Off(LD1);
	            LED_Off(LD3);
	            LED_On(LD2);
	        } else {
	            LED_On(LD1);
	            LED_On(LD3);
	            LED_Off(LD2);
	        }
	        state = !state;
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
  MX_ETH_Init();
  MX_USART3_UART_Init();
  MX_USB_OTG_FS_PCD_Init();

  /* USER CODE BEGIN 2 */

  // Inicializar el driver de anti-rebote
  debounceFSM_init();

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  // Actualizar la MEF de anti-rebote
	  debounceFSM_update();


      // // Verificar si se presionó el botón usando readKey()
      if (readKey())
      {
    	  sequence = (sequence + 1) % 4; // Cambiar a la siguiente secuencia
    	  // Reiniciar las variables de inicialización al cambiar de secuencia
    	  for (int i = 0; i < num_leds; i++) {
    		  LED_Off((led_T)i);
    	  }
      }

      // Ejecutar la secuencia actual
      switch (sequence) {
          case 0:
              Secuencia1();
              break;
          case 1:
              Secuencia2();
              break;
          case 2:
              Secuencia3();
              break;
          case 3:
              Secuencia4();
              break;
          default:
              break;
      }
  }

  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
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
  * @brief ETH Initialization Function
  * @param None
  * @retval None
  */
static void MX_ETH_Init(void)
{
  static uint8_t MACAddr[6];

  heth.Instance = ETH;
  MACAddr[0] = 0x00;
  MACAddr[1] = 0x80;
  MACAddr[2] = 0xE1;
  MACAddr[3] = 0x00;
  MACAddr[4] = 0x00;
  MACAddr[5] = 0x00;
  heth.Init.MACAddr = &MACAddr[0];
  heth.Init.MediaInterface = HAL_ETH_RMII_MODE;
  heth.Init.RxBuffLen = 1524; // Cambiado a RxBuffLen


  if (HAL_ETH_Init(&heth) != HAL_OK)
  {
    Error_Handler();
  }

  memset(&TxConfig, 0, sizeof(TxConfig));
  TxConfig.Attributes = ETH_TX_PACKETS_FEATURES_CSUM | ETH_TX_PACKETS_FEATURES_CRCPAD;
  TxConfig.ChecksumCtrl = ETH_CHECKSUM_IPHDR_PAYLOAD_INSERT_PHDR_CALC;
  TxConfig.CRCPadCtrl = ETH_CRC_PAD_INSERT;
}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USB_OTG_FS Initialization Function
  * @param None
  * @retval None
  */
static void MX_USB_OTG_FS_PCD_Init(void)
{
  hpcd_USB_OTG_FS.Instance = USB_OTG_FS;
  hpcd_USB_OTG_FS.Init.dev_endpoints = 4;
  hpcd_USB_OTG_FS.Init.speed = PCD_SPEED_FULL;
  hpcd_USB_OTG_FS.Init.dma_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
  hpcd_USB_OTG_FS.Init.Sof_enable = ENABLE;
  hpcd_USB_OTG_FS.Init.low_power_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.lpm_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.battery_charging_enable = ENABLE;
  if (HAL_PCD_Init(&hpcd_USB_OTG_FS) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
/*void MX_GPIO_Init(void)
{*/
  /*GPIO_InitTypeDef GPIO_InitStruct = {0};*/

  /* GPIO Ports Clock Enable */
  /*HAL_RCC_GPIOC_CLK_ENABLE();*/
/*HAL_RCC_GPIOH_CLK_ENABLE();*/
  /*HAL_RCC_GPIOA_CLK_ENABLE();*/
  /*HAL_RCC_GPIOB_CLK_ENABLE();*/

  /*Configure GPIO pin Output Level */
  /*HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_7|GPIO_PIN_14, GPIO_PIN_RESET);*/

  /*Configure GPIO pin : PC13 */
  /*GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);*/

  /*Configure GPIO pins : PB0 PB7 PB14 */
  /*GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_7|GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}*/

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

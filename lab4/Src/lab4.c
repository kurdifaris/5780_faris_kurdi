#include "main.h"
#include "stm32f0xx_hal.h"
#include "usart.h"

void SystemClock_Config(void);

// /dev/tty.usbserial-A5069RR4

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  /* Configure the system clock */
  SystemClock_Config();

  USART3_GPIO_Init();
  USART3_Init();

  GPIOC->MODER |= (GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0 | GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0);

  USART_TransmitString("checkoff 1 type r, g, b, o to toggle LEDs\r\n");
  // USART_TransmitString("checkoff 2\r\n");


  while (1)
  {
  
  // // 1st checkoff
  // // flag for normal checkoff 1 use, due to interrupt implementation
  // if (rx_flag) {
  //     char input = rx_char; 
  //     rx_flag = 0;
          
  //   if (input == 'r') { GPIOC->ODR ^= GPIO_ODR_6; } 
  //     else if (input == 'b') { GPIOC->ODR ^= GPIO_ODR_7; } 
  //     else if (input == 'g') { GPIOC->ODR ^= GPIO_ODR_9; } 
  //     else if (input == 'o') { GPIOC->ODR ^= GPIO_ODR_8; } 
  //     else { USART_TransmitString("invalid key\r\n"); }
  // }
  // }

  // 2nd checkoff
  USART_TransmitString("CMD? ");

    // wait for color
    while (rx_flag == 0);
    char color = rx_char;
    rx_flag = 0;
    USART_TransmitCharacter(color);
    if (color != 'r' && color != 'g' && color != 'b' && color != 'o') {
        USART_TransmitString("\r\ninvalid color\r\n");
        continue;
    }

    // wait for type of action
    while (rx_flag == 0); 
    char action = rx_char;
    rx_flag = 0;
    USART_TransmitCharacter(action);
    USART_TransmitString("\r\n");

    // figure out which pin
    uint32_t pin = 0;
    if (color == 'r') pin = GPIO_ODR_6;
    if (color == 'b') pin = GPIO_ODR_7;
    if (color == 'o') pin = GPIO_ODR_8;
    if (color == 'g') pin = GPIO_ODR_9;

    // action
    if (action == '0') {
        GPIOC->BSRR = (pin << 16); // off
        USART_TransmitString("off\r\n");
    } 
    else if (action == '1') {
        GPIOC->BSRR = pin;         // on
        USART_TransmitString("on\r\n");
    } 
    else if (action == '2') {
        GPIOC->ODR ^= pin;         // toggle
        USART_TransmitString("toggle\r\n");
    } 
    else {
        USART_TransmitString("invalid action\r\n");
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
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
  /* User can add their own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
}

#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add their own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
}
#endif /* USE_FULL_ASSERT */

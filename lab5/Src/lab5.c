#include "main.h"
#include "stm32f0xx_hal.h"

void SystemClock_Config(void);

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
  
  RCC->AHBENR |= RCC_AHBENR_GPIOBEN | RCC_AHBENR_GPIOCEN; //gpio b + c clock enable
  RCC->APB1ENR |= RCC_APB1ENR_I2C2EN; //i2c2 clock enable

  //pb11
  GPIOB->MODER   &= ~(3 << (11*2));
  GPIOB->MODER   |=  (2 << (11*2));
  GPIOB->OTYPER  |=  (1 << 11);
  GPIOB->AFR[1]  &= ~(0xF << ((11-8)*4));
  GPIOB->AFR[1]  |=  (1   << ((11-8)*4));

  //pb13
  GPIOB->MODER   &= ~(3 << (13*2));
  GPIOB->MODER   |=  (2 << (13*2));
  GPIOB->OTYPER  |=  (1 << 13);
  GPIOB->AFR[1]  &= ~(0xF << ((13-8)*4));
  GPIOB->AFR[1]  |=  (5   << ((13-8)*4));

  //pb14
  GPIOB->MODER   &= ~(3 << (14*2));
  GPIOB->MODER   |=  (1 << (14*2));
  GPIOB->OTYPER  &= ~(1 << 14);
  GPIOB->ODR     |=  (1 << 14);

  //pc0
  GPIOC->MODER   &= ~(3 << (0*2));
  GPIOC->MODER   |=  (1 << (0*2));
  GPIOC->OTYPER  &= ~(1 << 0);
  GPIOC->ODR     |=  (1 << 0);

  I2C2->TIMINGR = (1 << 28) | (0x4 << 20) | (0x2 << 16) | (0xF << 8) | (0x13 << 0);
  I2C2->CR1 |= I2C_CR1_PE;

      // //clear and set sadd and nbytes
      // I2C2->CR2 &= ~((0x7F << 16) | (0x3FF << 0));
      // I2C2->CR2 |= (1 << 16) | (0x69 << 1) | I2C_CR2_START;

      // while (!(I2C2->ISR & (I2C_ISR_TXIS | I2C_ISR_NACKF)));

      // //write the WHO_AM_I reg
      // I2C2->TXDR = 0x0F;

      // while (!(I2C2->ISR & I2C_ISR_TC));

      // //setup read
      // I2C2->CR2 &= ~((0x7F << 16) | (0x3FF << 0));
      // I2C2->CR2 |= (1 << 16) | (0x69 << 1) | I2C_CR2_RD_WRN | I2C_CR2_START;

      // //wait
      // while (!(I2C2->ISR & (I2C_ISR_RXNE | I2C_ISR_NACKF)));
      // while (!(I2C2->ISR & I2C_ISR_TC));
      // uint8_t who_am_i = I2C2->RXDR;

      // //bus
      // I2C2->CR2 |= I2C_CR2_STOP;           // this line was missing
      // while (!(I2C2->ISR & I2C_ISR_STOPF));  // wait for stop to complete
      // I2C2->ICR |= I2C_ICR_STOPCF;           // clear the stop flag
      // HAL_Delay(10);
  
  // GPIO_InitTypeDef TEST = {GPIO_PIN_6, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW};
  // HAL_GPIO_Init(GPIOC, &TEST);
  // while(1) {
  //   GPIOC->ODR ^= (1 << 6);
  //   HAL_Delay(who_am_i == 0xD3 ? 200 : 1000);
  // }

  //write 0x0B to CTRL_REG1
  I2C2->CR2 = (0x69 << 1) | (2 << 16) | (0 << 10) | (1 << 13);
  while (!(I2C2->ISR & I2C_ISR_TXIS) && !(I2C2->ISR & I2C_ISR_NACKF));
  I2C2->TXDR = 0x20;
  while (!(I2C2->ISR & I2C_ISR_TXIS) && !(I2C2->ISR & I2C_ISR_NACKF));
  I2C2->TXDR = 0x0B;
  while (!(I2C2->ISR & I2C_ISR_TC));
  I2C2->CR2 |= I2C_CR2_STOP;
  while (!(I2C2->ISR & I2C_ISR_STOPF));
  I2C2->ICR |= I2C_ICR_STOPCF;
  HAL_Delay(10);

  GPIO_InitTypeDef LED = {GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW};
  HAL_GPIO_Init(GPIOC, &LED);

  while (1)
  {
    uint8_t gyroVals[4];
    uint8_t reg = 0x28;

    for (int i = 0; i < 4; i++)
    {
      I2C2->CR2 = (0x69 << 1) | (1 << 16);
      I2C2->CR2 |= I2C_CR2_START;
      while (!(I2C2->ISR & I2C_ISR_TXIS));
      I2C2->TXDR = reg;
      while (!(I2C2->ISR & I2C_ISR_TC));

      I2C2->CR2 = (0x69 << 1) | (1 << 16) | (1 << 10);
      I2C2->CR2 |= I2C_CR2_START;
      while (!(I2C2->ISR & I2C_ISR_RXNE));
      gyroVals[i] = I2C2->RXDR;
      I2C2->CR2 |= I2C_CR2_STOP;
      while (!(I2C2->ISR & I2C_ISR_STOPF));
      I2C2->ICR |= I2C_ICR_STOPCF;

      reg++;
    }

    int16_t x = (int16_t)((gyroVals[1] << 8) | gyroVals[0]);
    int16_t y = (int16_t)((gyroVals[3] << 8) | gyroVals[2]);

    GPIOC->ODR &= ~((1 << 6) | (1 << 7) | (1 << 8) | (1 << 9));
    if      (x >  500) GPIOC->ODR |= (1 << 6);
    else if (x < -500) GPIOC->ODR |= (1 << 7);
    if      (y >  500) GPIOC->ODR |= (1 << 8);
    else if (y < -500) GPIOC->ODR |= (1 << 9);

    HAL_Delay(100);
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

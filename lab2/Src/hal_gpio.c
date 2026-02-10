#include <stdint.h>
#include <stm32f0xx_hal.h>
#include <stm32f0xx_hal_gpio.h>
#include "main.h"

void Config_EXTI(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    __HAL_RCC_SYSCFG_CLK_ENABLE();

    // unmask EXTI0
    EXTI->IMR |= EXTI_IMR_IM0;

    // trigger on rising edge
    EXTI->RTSR |= EXTI_RTSR_TR0;

    EXTI->FTSR &= ~EXTI_FTSR_TR0; // make sure falling trigger is disabled

    SYSCFG->EXTICR[0] &= ~(SYSCFG_EXTICR1_EXTI0); // clear EXTI0 bits
}
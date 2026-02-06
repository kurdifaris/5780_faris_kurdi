#include <stdint.h>
#include <stm32f0xx_hal.h>
#include <stm32f0xx_hal_gpio.h>

void Config_EXTI(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    // unmask EXTI0
    EXTI->IMR |= EXTI_IMR_IM0;

    // trigger on rising edge
    EXTI->RTSR |= EXTI_RTSR_TR0;

    EXTI->FTSR &= ~EXTI_FTSR_TR0; // make sure falling trigger is disabled
}
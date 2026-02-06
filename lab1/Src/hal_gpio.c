#include <stdint.h>
#include <stm32f0xx_hal.h>
#include <stm32f0xx_hal_gpio.h>

void My_HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init)
{
    // Configure LED pins ----
    if (GPIOx == GPIOC) {
    // clear bits then set 1
    GPIOC->MODER &= ~((3 << 12) | (3 << 14));
    GPIOC->MODER |= (GPIO_Init->Mode << 12) | (GPIO_Init->Mode << 14);

    // set pull-up pull-down
    GPIOC->PUPDR &= ~((3 << 12) | (3 << 14));
    GPIOC->PUPDR |= (GPIO_Init->Pull << 12) | (GPIO_Init->Pull << 14);

    // set speed
    GPIOC->OSPEEDR &= ~((3 << 12) | (3 << 14));
    GPIOC->OSPEEDR |= (GPIO_Init->Speed << 12) | (GPIO_Init->Speed << 14); 
    }
    
    // Configure USER Button ----
    else if (GPIOx == GPIOA) {
    // clear and set
    GPIOA->MODER &= ~(3 << 0);
    GPIOA->MODER |= (GPIO_Init->Mode << 0); // pin 0

    // set pull-up pull-down
    GPIOA->PUPDR &= ~(3 << 0);
    GPIOA->PUPDR |= (GPIO_Init->Pull << 0);
    }
}

/*
void My_HAL_GPIO_DeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin)
{
}
*/

GPIO_PinState My_HAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    if (GPIOx->IDR & GPIO_Pin) {
        return GPIO_PIN_SET;
    }
    return GPIO_PIN_RESET;
}

void My_HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
{
    if (PinState == GPIO_PIN_SET) {
        // bits 0-15
        GPIOx->BSRR = (uint32_t)GPIO_Pin; 
    } else {
        // bits 16-31
        GPIOx->BSRR = (uint32_t)GPIO_Pin << 16; 
    }
}

void My_HAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    // toggle by XORing the output data register
    GPIOx->ODR ^= GPIO_Pin;
}

void Config_EXTI(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    // unmask EXTI0
    EXTI->IMR |= EXTI_IMR_IM0;

    // trigger on rising edge
    EXTI->RTSR |= EXTI_RTSR_TR0;

    EXTI->FTSR &= ~EXTI_FTSR_TR0; // make sure falling trigger is disabled
}


#include <stdint.h>
#include <stm32f0xx_hal.h>
#include <stm32f0xx_hal_gpio.h>

void My_HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init)
{
    // Configure LED pins ----
    // clear bits then set 1 bit for each pin
    GPIOx->MODER &= ~((3 << 12) | (3 << 14) | (3 << 16) | (3 << 18)); // pin 6,7,8,9
    GPIOx->MODER |=  ((1 << 12) | (1 << 14) | (1 << 16) | (1 << 18)); // set to output 01

    // set output type to push-pull
    GPIOx->OTYPER &= ~((1 << 6) | (1 << 7) | (1 << 8) | (1 << 9)); // pin 6,7,8,9

    // set speed to low
    GPIOx->OSPEEDR &= ~((3 << 12) | (3 << 14) | (3 << 16) | (3 << 18)); // pin 6,7,8,9

    // set no pull-up, pull-down
    GPIOx->PUPDR &= ~((3 << 12) | (3 << 14) | (3 << 16) | (3 << 18)); // pin 6,7,8,9

    // Configure USER Button ----
    // set mode to input 00
    GPIOA->MODER &= ~(3 << 0); // pin 0

    // set speed to low
    GPIOA->OSPEEDR &= ~(3 << 0); // pin 0

    // set no pull-up, pull-down (clear and then set to 10)
    GPIOA->PUPDR &= ~(3 << 0);
    GPIOA->PUPDR |=  (2 << 0); 
}


/*
void My_HAL_GPIO_DeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin)
{
}
*/

/*
GPIO_PinState My_HAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    return -1;
}
*/


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
    
}


#include <stdint.h>
#include <stm32f0xx_hal.h>
#include <stm32f0xx_hal_gpio.h>

void My_HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init)
{
    // Configure LED pins ----
    // clear bits then set 1 bit for each pin
    GPIOC->MODER &= ~((3 << 12) | (3 << 14) | (3 << 16) | (3 << 18)); 
    GPIOC->MODER |=  ((1 << 12) | (1 << 14) | (1 << 16) | (1 << 18));

    // set output type to push-pull
    GPIOC->OTYPER &= ~((1 << 6) | (1 << 7) | (1 << 8) | (1 << 9));

    // set speed to low
    GPIOC->OSPEEDR &= ~((3 << 12) | (3 << 14) | (3 << 16) | (3 << 18));

    // set no pull-up, pull-down
    GPIOC->PUPDR &= ~((3 << 12) | (3 << 14) | (3 << 16) | (3 << 18));

    // Configure USER Button ----
    
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

/*
void My_HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
{
}
*/

/*
void My_HAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
}
*/

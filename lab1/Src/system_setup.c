#include "main.h"
#include "stm32f072xb.h"

void HAL_RCC_GPIOC_CLK_Enable(void) {
    // enable GPIOC clock
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN; 
}

void HAL_RCC_GPIOA_CLK_Enable(void) {
    // enable GPIOA clock
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN; 
}
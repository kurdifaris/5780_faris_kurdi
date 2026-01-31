#include "main.h"
#include "stm32f072xb.h" //

void HAL_RCC_GPIOC_CLK_Enable(void) {
    // enable GPIOC clock
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN; 
}
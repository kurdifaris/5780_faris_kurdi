#include "timer.h"

void Timer_Interrupt(void) {
    __HAL_RCC_TIM2_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_InitTypeDef timerPin = {GPIO_PIN_8 | GPIO_PIN_9, GPIO_MODE_OUTPUT_PP, GPIO_SPEED_FREQ_LOW, GPIO_NOPULL};
    HAL_GPIO_Init(GPIOC, &timerPin);

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);

    TIM2->PSC = 8000 - 1; // 8MHz/8000 = 1kHz
    TIM2->ARR = 250 - 1; // 1kHz/250 = 4Hz

    TIM2->DIER |= TIM_DIER_UIE;
    TIM2->CR1 |= TIM_CR1_CEN;

    NVIC_EnableIRQ(TIM2_IRQn);
}
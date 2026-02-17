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

void PWM_Init(void) {
    __HAL_RCC_TIM3_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_InitTypeDef PWMPin = {GPIO_PIN_6 | GPIO_PIN_7, GPIO_MODE_AF_PP, GPIO_SPEED_FREQ_LOW, GPIO_NOPULL};
    HAL_GPIO_Init(GPIOC, &PWMPin);

    // set alternate function for TIM3 on PC6 and PC7
    GPIOC->AFR[0] &= ~((0xF << (6 * 4)) | (0xF << (7 * 4)));

    TIM3->PSC = 10 - 1; 
    TIM3->ARR = 1000; // 800Hz

    TIM3->CCMR1 |= (7 << TIM_CCMR1_OC1M_Pos);
    TIM3->CCMR1 |= (6 << TIM_CCMR1_OC2M_Pos); 

    TIM3->CCMR1 |= (TIM_CCMR1_OC1PE | TIM_CCMR1_OC2PE); // preload
    TIM3->CCER |= (TIM_CCER_CC1E | TIM_CCER_CC2E); // enable output

    // init duty cycle
    TIM3->CCR1 = 200;
    TIM3->CCR2 = 200;

    // start timer
    TIM3->CR1 |= TIM_CR1_CEN;
}
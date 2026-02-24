#include "usart.h"
#include "stm32f0xx.h"

void USART3_GPIO_Init(void) {
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;

    // set pins 10 and 11
    GPIOC->MODER &= ~(GPIO_MODER_MODER10 | GPIO_MODER_MODER11);
    GPIOC->MODER |= (GPIO_MODER_MODER10_1 | GPIO_MODER_MODER11_1);

    // alt function, pins 10 and 11
    GPIOC->AFR[1] &= ~(0x0000FF00); 
    GPIOC->AFR[1] |= (0x00001100);  
}

void USART3_Init(void) {
    RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
    USART3->BRR = 0x45; // set baud rate = 115200
    USART3->CR1 |= (USART_CR1_TE | USART_CR1_RE | USART_CR1_UE);
}

void USART_TransmitChar(char c) {
    while (!(USART3->ISR & USART_ISR_TXE));
    USART3->TDR = c;
}

void USART_TransmitString(char* str) {
    while (*str != '\0') {
        USART_TransmitChar(*str);
        str++;
    }
}

char USART_ReceiveChar(void) {
    while (!(USART3->ISR & USART_ISR_RXNE));
    return (char)(USART3->RDR);
}
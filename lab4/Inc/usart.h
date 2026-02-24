#ifndef USART_H
#define USART_H

#include "stm32f0xx.h"

extern volatile char rx_char;
extern volatile uint8_t rx_flag;

void USART3_GPIO_Init(void);
void USART3_Init(void);
void USART_TransmitCharacter(char c);
void USART_TransmitString(char* str);
char USART_ReceiveCharacter(void);

#endif /* USART_H */
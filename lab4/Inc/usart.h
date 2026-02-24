#ifndef USART_H
#define USART_H

void USART3_GPIO_Init(void);
void USART3_Init(void);
void USART_TransmitChar(char c);
void USART_TransmitString(char* str);
char USART_ReceiveChar(void);

#endif /* USART_H */
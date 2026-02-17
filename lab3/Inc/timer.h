#ifndef __TIMER_H
#define __TIMER_H

#include "stm32f0xx_hal.h"

void Timer_Interrupt(void);
void PWM_Init(void);

#endif /* __TIMER_H */
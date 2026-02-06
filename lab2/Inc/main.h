#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f0xx_hal.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void Error_Handler(void);
void Config_EXTI(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

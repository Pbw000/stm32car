#ifndef BUZZER_H
#define BUZZER_H
#include "stm32f10x.h"
void Buzzer_init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void buzz_ms(uint16_t ms);
void on(void);
void off(void);
#endif

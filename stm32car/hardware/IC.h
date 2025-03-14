#ifndef _IC_H
#define _IC_H
#include "stm32f10x.h"                  // Device header

void IC_Init(void);
uint16_t get_frequency(void);
float get_duty(void);
#endif

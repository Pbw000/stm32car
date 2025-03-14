#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H
#include "stm32f10x.h"
uint8_t isLightOn(void);
void Light_sensor_init(GPIO_TypeDef*, uint16_t);
#endif
